#ifndef XYZ_WRITER_H
#define XYZ_WRITER_H

#include <vector>
#include <string>

using namespace std;

namespace aasoni {

class XYZ_Writer
{
    public: 
        XYZ_Writer()
        { }

        ~XYZ_Writer()
        { }
        
        //Writes a file in X Y Z format
        //x (out) - x vector
        //y (out) - y vector
        //z (out) - z matrix
        //n (in) - length of x
        //m (in) - length of y
        //fileName (in) - The file name to read
        typedef vector<double> VEC;
        bool writeToFile(const VEC &x, const VEC &y, const vector<VEC> &z, const string &fileName);

    private:

        //not exposing copy constructor and copy assignement
        XYZ_Writer(const XYZ_Writer& reader);
        XYZ_Writer &operator=(const XYZ_Writer &reader);

};

} //end namespace aasoni


#endif
