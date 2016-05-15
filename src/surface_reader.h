#ifndef SURFACE_READER_H
#define SURFACE_READER_H

#include <vector>
#include <string>

using namespace std;

class SurfaceReader
{

    public:
        virtual ~SurfaceReader() {}

        typedef vector<double> VEC;
        virtual bool readFile(VEC *x, VEC *y, vector<VEC> *z) = 0;
        virtual void setFileName(const string &fileName) = 0;
};

#endif
