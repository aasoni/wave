#ifndef DRIVER_H 
#define DRIVER_H

#include <surface_reader.h>
#include <surface_writer.h>
#include <apply_init_wave.h>
#include <wave_simulator_2d.h>

using namespace std;

namespace aasoni {

int run(SurfaceReader   *reader,
        SurfaceWriter   *writer,
        ApplyInitWave   *applyWave,
        WaveSimulator2D *simulator,
        const string &surfaceFile,
        const string &outFilePrefix);

} //asoni

#endif
