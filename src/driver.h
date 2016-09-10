#ifndef DRIVER_H
#define DRIVER_H

#include <surface_reader.h>
#include <surface_writer.h>
#include <apply_init_wave.h>
#include <wave_simulator_2d.h>
#include <memory>

using namespace std;

namespace aasoni {

int run(shared_ptr<SurfaceReader>   &reader,
        shared_ptr<SurfaceWriter>   &writer,
        shared_ptr<ApplyInitWave>   &applyWave,
        shared_ptr<WaveSimulator2D> &simulator,
        const string &surfaceFile,
        const string &outFilePrefix);

} //asoni

#endif
