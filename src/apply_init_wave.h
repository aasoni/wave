#ifndef APPLY_INIT_WAVE_H
#define APPLY_INIT_WAVE_H

#include <vector>

using namespace std;

namespace aasoni {

// ApplyInitWave
// pure virtual base class
class ApplyInitWave
{
    public:

        virtual ~ApplyInitWave() { }

        typedef vector<double> VEC;
        typedef vector<VEC> MAT;
        virtual void operator()(VEC *x, VEC *y, MAT *surf) = 0;

};

} //aasoni

#endif
