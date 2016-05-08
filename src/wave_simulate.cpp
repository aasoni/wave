#include <iostream>
#include <sstream>

#include <apply_init_wave.h>
#include <param_reader.h>
#include <utility.h>
#include <xyz_reader.h>
#include <xyz_writer.h>
#include <wave_simulator_2d.h>

using namespace aasoni;
using namespace std;

namespace {

    bool parseArguments(std::string *paramFile,
                        std::string *outFilePrefix,
                        int argc, char *argv[])
    {
        if (argc < 5)
        {
            cout << "Usage is -p <param_file> -o <out_prefix>" << endl;
            return false;
        }
        else
        {
            for (size_t i = 1; i < argc; ++i)
            {
                if (string(argv[i]) == "-p")
                {
                    *paramFile = argv[i+1];
                    ++i;
                }
                else if (string(argv[i]) == "-o")
                {
                    *outFilePrefix = argv[i+1];
                    ++i;
                }
                else
                {
                    cout << "Not enough or invalid arguments." << endl;
                    return false;
                }
            }
            return true;
        }
    }

} //anonymous namespace 

int main(int argc, char *argv[] )
{
    //get command line arguments
    std::string paramFile, outFilePrefix;
    if(!parseArguments(&paramFile, &outFilePrefix, argc, argv))
        return 0;

    //read parameter file
    ParamReader paramReader(paramFile);

    //get data file info
    string fileName = paramReader.getDataFileName();
    size_t xLength = paramReader.getXLength();
    size_t yLength = paramReader.getYLength();

    //read data
    VEC latitude, longitude;
    MAT bathymetry;
    XYZ_Reader reader;
    if(!reader.readFile(&latitude, &longitude, &bathymetry, xLength, yLength, fileName))
    {
        cout << "Unable to read data" << endl;
        return 1;
    }

    //convert data to surface
    MAT height = bathymetry;
    bathymetryToHeight(&height);

    //   ADD WAVE TO SURFACE
    //read wave data
    double amplitude = paramReader.getWaveAmplitude();
    double xPos = paramReader.getWaveX();
    double yPos = paramReader.getWaveY();
    double xSigma = paramReader.getWaveSigmaX();
    double ySigma = paramReader.getWaveSigmaY();
    double c = paramReader.getWaveC();
    MAT wave = height;

    ApplyInitWave applyWave(amplitude, xPos, yPos, xSigma, ySigma, c);
    applyWave(&latitude, &longitude, &wave);

    //write initial wave
    MAT output;
    XYZ_Writer writer;
    heightAndBathymetryToSurface(&output, bathymetry, wave);
    writer.writeToFile(latitude,longitude,output,"data/surface.xyz");

    //Simulate propagation
    size_t steps = paramReader.getSimulationSteps();
    double deltaX = paramReader.getDeltaX();
    double deltaY = paramReader.getDeltaY();
    double deltaT = paramReader.getDeltaT();
    WaveSimulator2D simulator(steps, deltaX, deltaY, deltaT, wave, &wave);

    size_t iter = 0;
    string outputFilename;
    while(simulator.next())
    {
        if(iter % 10 == 1)
            cout << "completed " << iter << " iterations." << endl;
        ++iter;
        ostringstream os;
        os << outFilePrefix << "_" << iter << ".xyz";
        outputFilename = os.str();

        //write output
        heightAndBathymetryToSurface(&output, bathymetry, wave);
        writer.writeToFile(latitude,longitude,output,outputFilename);
    }

}
