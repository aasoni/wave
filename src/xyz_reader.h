#ifndef XYZ_READER_H
#define XYZ_READER_H

#include <vector>
#include <string>

using namespace std;

namespace aasoni {

class XYZ_Reader
{
    public: 
        XYZ_Reader()
        { }

        ~XYZ_Reader()
        { }
        
        //Reads a file in X Y Z format
        //x (out) - x vector
        //y (out) - y vector
        //z (out) - z matrix
        //n (in) - length of x
        //m (in) - length of y
        //fileName (in) - The file name to read
        typedef vector<double> VEC;
        bool readFile(VEC *x, VEC *y, vector<VEC> *z, size_t n,
                      size_t m, const string &fileName);

    private:

        //not exposing copy constructor and copy assignement
        XYZ_Reader(const XYZ_Reader& reader);
        XYZ_Reader &operator=(const XYZ_Reader &reader);

};

} //end namespace aasoni


#endif
