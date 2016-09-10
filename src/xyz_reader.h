#ifndef XYZ_READER_H
#define XYZ_READER_H

#include <surface_reader.h>

using namespace std;

namespace aasoni {

class XYZ_Reader : public SurfaceReader
{
    public:

        XYZ_Reader() { }
        ~XYZ_Reader() { }

        //Reads a file in X Y Z format
        //x (out) - x vector
        //y (out) - y vector
        //z (out) - z matrix
        //n (in) - length of x
        //m (in) - length of y
        //fileName (in) - The file name to read
        bool readFile(VEC *x, VEC *y, vector<VEC> *z);

        void setFileName(const string &fileName)
        {
            m_fileName = fileName;
        }

        void setYLength(size_t n)
        {
            m_yLength = n;
        }

        void setXLength(size_t m)
        {
            m_xLength = m;
        }

    protected:
        //not exposing copy constructor and copy assignement
        XYZ_Reader(const XYZ_Reader& reader);
        XYZ_Reader &operator=(const XYZ_Reader &reader);

        size_t m_yLength, m_xLength;
        string m_fileName;
};

} //end namespace aasoni


#endif
