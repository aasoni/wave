#ifndef SURFACE_WRITER_H
#define SURFACE_WRITER_H

#include <vector>
#include <string>

using namespace std;

namespace aasoni {

class SurfaceWriter
{
    public: 
        virtual ~SurfaceWriter() { }
        
        typedef vector<double> VEC;
        virtual bool writeToFile(const VEC &x, const VEC &y, const vector<VEC> &z) = 0;
        virtual void setFileName(const string &fileName) = 0;

};

} //end namespace aasoni

#endif
