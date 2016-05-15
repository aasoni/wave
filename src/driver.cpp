#include <driver.h>
#include <utility.h>
#include <iostream>
#include <sstream>

using namespace std;

namespace aasoni {

int run(SurfaceReader   *reader,
        SurfaceWriter   *writer,
        ApplyInitWave   *applyWave,
        WaveSimulator2D *simulator,
        const string &surfaceFile,
        const string &outFilePrefix)
{
    if(!reader || !writer || !applyWave || !simulator)
    {
        cerr << "Invalid inputs to run simulation" << endl;
        return 1;
    }

    //read data
    VEC latitude, longitude;
    MAT bathymetry;
    reader->setFileName(surfaceFile);
    if(!reader->readFile(&latitude, &longitude, &bathymetry))
    {
        cout << "Reader was unable to read data. " << endl;
        return 1;
    }

    //convert data to surface
    MAT height = bathymetry;
    bathymetryToHeight(&height);

    //Add wave to surface
    MAT wave = height;
    (*applyWave)(&latitude, &longitude, &wave);

    //write initial wave
    MAT output;
    size_t iter = 1;
    heightAndBathymetryToSurface(&output, bathymetry, wave);
    ostringstream outFileOS;
    outFileOS << outFilePrefix << "_" << iter << ".xyz";
    writer->setFileName(outFileOS.str());
    writer->writeToFile(latitude,longitude,output);

    //initialize surface for simulator
    simulator->setWavedSurface(wave);
    simulator->setSimulationSurface(&wave);

    //time march simulator
    string outputFilename;
    while(simulator->next())
    {
        ++iter;
        if(iter % 10 == 1)
            cout << "completed " << iter << " iterations." << endl;
        ostringstream os;
        os << outFilePrefix << "_" << iter << ".xyz";
        outputFilename = os.str();

        //write output
        heightAndBathymetryToSurface(&output, bathymetry, wave);
        writer->setFileName(outputFilename);
        writer->writeToFile(latitude,longitude,output);
    }

    return 0;
}

} //aasoni
