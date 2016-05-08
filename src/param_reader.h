#ifndef PARAM_READER_H
#define PARAM_READER_H

#include <string>

using namespace std;

namespace aasoni {

class ParamReader {

    public:
        ParamReader(const string &parameterFileName);

        //read xyz data file name
        string getDataFileName()
        { return m_dataFileName; }

        //read wave parameters from file
        double getWaveAmplitude()
        { return m_wAmplitude; }

        double getWaveSigmaX()
        { return m_wSigmaX; }

        double getWaveSigmaY()
        { return m_wSigmaY; }

        double getWaveX()
        { return m_wX; }

        double getWaveY()
        { return m_wY; }

        double getWaveC()
        { return m_wC; }

        size_t getXLength()
        { return m_xLength; }

        size_t getYLength()
        { return m_yLength; }

        size_t getSimulationSteps()
        { return m_steps; }

        double getDeltaX()
        { return m_deltaX; }

        double getDeltaY()
        { return m_deltaY; }

        double getDeltaT()
        { return m_deltaT; }

    private:

        enum ParameterType {
            EMPTY_LINE,
            DATA_FILE_NAME,
            X_LENGTH,
            Y_LENGTH,
            WAVE_AMPLITUDE,
            WAVE_SIGMA_X,
            WAVE_SIGMA_Y,
            WAVE_X,
            WAVE_Y,
            WAVE_C,
            STEPS,
            DELTA_X,
            DELTA_Y,
            DELTA_T,
            COMMENT,
            INVALID_TYPE
        };

        void readParameter(const string &line);

        ParameterType paramNameToType(const string &paramName);

        //xyz file name
        string m_dataFileName;

        //xyz sizes
        size_t m_xLength;
        size_t m_yLength;

        //wave parameters
        double m_wAmplitude;
        double m_wSigmaX;
        double m_wSigmaY;
        double m_wX;
        double m_wY;
        double m_wC;

        //simulation parameters
        size_t m_steps;
        double m_deltaX;
        double m_deltaY;
        double m_deltaT;
        

};

} //aasoni

#endif 
