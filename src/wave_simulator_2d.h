#ifndef WAVE_SIMULATOR_2D_H
#define WAVE_SIMULATOR_2D_H

#include <utility.h>

namespace aasoni {

//Pure virtual interface for a generic 2D wave simulator
class WaveSimulator2D
{
    public:
        //next will modiy the wave passed by pointer below
        virtual bool next() = 0;

        //set initial surface with wave
        virtual void setWavedSurface(const MAT &init) = 0;

        //set surface that is modified at each simulation step
        virtual void setSimulationSurface(MAT *wave) = 0;

        virtual ~WaveSimulator2D() {}
};

} //aasoni

#endif
