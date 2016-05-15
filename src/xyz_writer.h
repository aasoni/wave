#ifndef XYZ_WRITER_H
#define XYZ_WRITER_H

#include <surface_writer.h>

using namespace std;

namespace aasoni {

class XYZ_Writer : public SurfaceWriter
{
    public: 

        XYZ_Writer() { }
        ~XYZ_Writer() { }

        //Writes a file in X Y Z format
        //x (out) - x vector
        //y (out) - y vector
        //z (out) - z matrix
        //n (in) - length of x
        //m (in) - length of y
        //fileName (in) - The file name to read
        bool writeToFile(const VEC &x, const VEC &y, const vector<VEC> &z);

        void setFileName(const string &fileName)
        {
            m_fileName = fileName;
        }

    private:

        //not exposing copy constructor and copy assignement
        XYZ_Writer(const XYZ_Writer& reader);
        XYZ_Writer &operator=(const XYZ_Writer &reader);

        string m_fileName;
};

} //end namespace aasoni


#endif
