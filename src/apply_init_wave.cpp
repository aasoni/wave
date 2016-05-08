#include <apply_init_wave.h>

#include <math.h>

namespace aasoni {

double ApplyInitWave::gaussianBell(double x, double y)
{
    return m_amplitude * exp(-0.5*pow((x - pow(m_xPos,m_c))/m_xSigma, 2.0)
                             -0.5*pow((y - pow(m_yPos,m_c))/m_ySigma, 2.0));
}

void ApplyInitWave::operator()(VEC *x, VEC *y, MAT *surface)
{
    if(!x || !y || !surface) return;

    size_t m = surface->size();
    if(m == 0) return; //input is empty

    size_t n = (*surface)[0].size();

    for(size_t i = 0; i != m; ++i)
    {
        for(size_t j =0; j != n; ++j)
        {
            double v = (*surface)[i][j];
            if(v < 0.0 || isnan(v))
                continue;

            (*surface)[i][j] = v + gaussianBell((*x)[j], (*y)[i]);
        }
    }

}

} //aasoni
