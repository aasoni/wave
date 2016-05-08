#ifndef APPLY_INIT_WAVE_H
#define APPLY_INIT_WAVE_H

#include <vector>

using namespace std;

namespace aasoni {

class ApplyInitWave
{
    public:
        ApplyInitWave(double amplitude,
                      double xPos,
                      double yPos,
                      double xSigma,
                      double ySigma,
                      double c)
            : m_amplitude(amplitude)
            , m_xPos(xPos)
            , m_yPos(yPos)
            , m_xSigma(xSigma)
            , m_ySigma(ySigma)
            , m_c(c)
        { }

        typedef vector<double> VEC;
        typedef vector<VEC> MAT;

        void operator()(VEC *x, VEC *y, MAT *surf);

    private:

        double gaussianBell(double x, double y);

        double m_amplitude;
        double m_xPos;
        double m_yPos;
        double m_xSigma;
        double m_ySigma;
        double m_c;

};

} //aasoni

#endif
