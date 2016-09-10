#include <utility.h>
#include <iostream>

#include <limits>
#include <cmath>

namespace aasoni {

static const double EPS=1e-10;

void bathymetryToHeight(MAT *b)
{
    if(!b) return;

    size_t m = b->size();
    if(m == 0) //input is empty
        return;

    size_t n = (*b)[0].size();
    for(size_t i = 0; i != m; ++i)
    {
        for(size_t j = 0; j != n; ++j)
        {
            if( (*b)[i][j] < EPS + 0 )
                //set all sea (bathymetry < 0) to 0
                (*b)[i][j] = 0.0;
            else
                //set all land (bathymetry > 0) to NaNQ
                (*b)[i][j] = numeric_limits<double>::quiet_NaN();
        }
    }
}

void heightAndBathymetryToSurface(MAT *out, const MAT &b, const MAT &h)
{
    //invalid out pointer
    if(!out) return;

    size_t m = b.size();

    //check if is empty
    if(m == 0) return;

    size_t n = b[0].size();

    out->resize(m);
    for(size_t i = 0; i != m; ++i)
    {
        (*out)[i].resize(n);
        for(size_t j = 0; j != n; ++j)
        {
            if(std::isnan(h[i][j]))
                (*out)[i][j] = b[i][j];
            else
                (*out)[i][j] = h[i][j];
        }
    }
}

bool epsEqual(double a, double b)
{
    return abs(a-b) < EPS;
}

} //aasoni
