#include <iostream>

#include <driver.h>
#include <param_reader.h>
#include <xyz_reader.h>
#include <xyz_writer.h>
#include <lf_wave_simulator_2d.h>
#include <apply_gauss_wave.h>

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
    string surfaceFileName = paramReader.getDataFileName();
    size_t xLength = paramReader.getXLength();
    size_t yLength = paramReader.getYLength();

    //initialize reader
    XYZ_Reader *reader = new XYZ_Reader();
    reader->setXLength(xLength);
    reader->setYLength(yLength);

    //initialize writer
    XYZ_Writer *writer = new XYZ_Writer();

    //Initialize class to add wave to surface
    double amplitude = paramReader.getWaveAmplitude();
    double xPos = paramReader.getWaveX();
    double yPos = paramReader.getWaveY();
    double xSigma = paramReader.getWaveSigmaX();
    double ySigma = paramReader.getWaveSigmaY();
    double c = paramReader.getWaveC();
    ApplyGaussWave *initWave = new ApplyGaussWave(amplitude, xPos, yPos, xSigma, ySigma, c);
    
    //Initialize Simualtor
    size_t steps = paramReader.getSimulationSteps();
    double deltaX = paramReader.getDeltaX();
    double deltaY = paramReader.getDeltaY();
    double deltaT = paramReader.getDeltaT();
    WaveSimulator2D *simulator = new LFWaveSimulator2D(steps, deltaX, deltaY, deltaT);

    //run simulation
    run(reader, writer, initWave, simulator, surfaceFileName, outFilePrefix);
}
