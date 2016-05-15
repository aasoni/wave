#ifndef LF_WAVE_SIMULATOR_2D_H
#define LF_WAVE_SIMULATOR_2D_H

#include <wave_simulator_2d.h>
#include <vector>

using namespace std;

namespace aasoni {

//Implements the WaveSimulator2D Interface
//using the leap frog finite difference method
class LFWaveSimulator2D : public WaveSimulator2D
{
    public:

        enum BOUNDARY_CONDITION {
            SOMMERFELD, REFLECTIVE
        };

        LFWaveSimulator2D(size_t steps,
                          double deltaX,
                          double deltaY,
                          double deltaT)
            : m_steps(steps)
            , m_deltaX(deltaX)
            , m_deltaY(deltaY)
            , m_deltaT(deltaT)
            , m_lambdaX(deltaT/deltaX)
            , m_lambdaY(deltaT/deltaY)
        {
            m_qX = (m_deltaX - m_deltaT)/(m_deltaX + m_deltaT);
            m_qY = (m_deltaY - m_deltaT)/(m_deltaY + m_deltaT);
        }

        void setWavedSurface(const MAT &init)
        {
            m_prevWave = new MAT(init);
            m_ySize = init.size();
            m_xSize = init.empty() ? 0 : init[0].size();
        }

        void setSimulationSurface(MAT *wave)
        {
            m_wave = wave;
        }

        ~LFWaveSimulator2D()
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
        double boundaryStep(size_t i, size_t j, BOUNDARY_TYPE type);

        //corner steps
        enum CORNER_TYPE {
            BOTTOM_LEFT, BOTTOM_RIGHT, TOP_LEFT, TOP_RIGHT 
        };
        double cornerStep(size_t i, size_t j, CORNER_TYPE type);

        //determine boundary type
        void boundaryType(bool *corner, BOUNDARY_TYPE *bType, 
                          CORNER_TYPE *cType, size_t i, size_t j);

        //not exposing copy assignmen and copy constructor
        LFWaveSimulator2D(const LFWaveSimulator2D &reader);
        LFWaveSimulator2D &operator=(const LFWaveSimulator2D &reader);
};

} //aasoni

#endif
