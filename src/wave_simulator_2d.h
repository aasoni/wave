#ifndef WAVE_SIMULATOR_2D_H
#define WAVE_SIMULATOR_2D_H

#include <vector>
#include <utility.h>
#include <iostream>

using namespace std;

namespace aasoni {

class WaveSimulator2D
{
    public:

        enum BOUNDARY_CONDITION {
            SOMMERFELD, REFLECTIVE
        };

        WaveSimulator2D(size_t steps,
                        double deltaX,
                        double deltaY,
                        double deltaT,
                        const MAT &init,
                        MAT* wave)
            : m_steps(steps)
            , m_deltaX(deltaX)
            , m_deltaY(deltaY)
            , m_deltaT(deltaT)
            , m_lambdaX(deltaT/deltaX)
            , m_lambdaY(deltaT/deltaY)
            , m_ySize(init.size())
            , m_xSize(init.empty() ? 0 : init[0].size())
            , m_boundaryCond(SOMMERFELD)
            , m_wave(wave)
        {
            m_qX = (m_deltaX - m_deltaT)/(m_deltaX + m_deltaT);
            m_qY = (m_deltaY - m_deltaT)/(m_deltaY + m_deltaT);
            m_prevWave = new MAT(init);
        }

        ~WaveSimulator2D()
        {
            delete m_prevWave;
        }

        bool next();

    private:
        //simulation parameters
        size_t m_steps;
        double m_deltaX;
        double m_deltaY;
        double m_deltaT;
        double m_lambdaX;
        double m_lambdaY;
        size_t m_ySize;
        size_t m_xSize;
        double m_qX;
        double m_qY;

        //boundary condition
        BOUNDARY_CONDITION m_boundaryCond;

        //wave that will be marched forward
        MAT *m_wave;
        MAT *m_prevWave;
        MAT *m_nextWave;

        //boundary step
        double boundaryStep(size_t i, size_t j);

        //internal step
        double internalStep(size_t i, size_t j);

        //boundary steps
        enum BOUNDARY_TYPE {
            LEFT, RIGHT, UPPER, LOWER
        };
        double boundaryStepRef(size_t i, size_t j, BOUNDARY_TYPE type);
        double boundaryStepSom(size_t i, size_t j, BOUNDARY_TYPE type);

        //corner steps
        enum CORNER_TYPE {
            BOTTOM_LEFT, BOTTOM_RIGHT, TOP_LEFT, TOP_RIGHT 
        };
        double cornerStepRef(size_t i, size_t j, CORNER_TYPE type);
        double cornerStepSom(size_t i, size_t j, CORNER_TYPE type);

        //determine boundary type
        void boundaryType(bool *corner, BOUNDARY_TYPE *bType, 
                          CORNER_TYPE *cType, size_t i, size_t j);
};

} //aasoni

#endif
