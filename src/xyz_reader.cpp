#include <xyz_reader.h>

#include <fstream>
#include <iostream>

namespace aasoni {
   
//Reads file in format:
//x_1   y_m     z_1_m
//x_2   y_m     z_1_m
//x_3   y_m     z_1_m
//      .
//      .
//x_n   y_m     z_1_(m-1)
//x_1   y_(m_1) z_1_(m-1)
//      .
//      .
//x_n   y_1     z_n_1
bool XYZ_Reader::readFile(VEC *x, VEC *y, vector<VEC> *z)
{
    if(!x || !y || !z)
        return false;

    ifstream fhandle(m_fileName.c_str(), ifstream::in);
    if(!fhandle.good())
        return false;

    size_t &m = m_yLength;
    size_t &n = m_xLength;

    //allocate size for data vectors
    x->resize(n);
    y->resize(m);
    z->resize(m);
    for(size_t i=0; i != m; ++i)
        (*z)[i].resize(n);

    size_t i = 0, xIdx = 0, yIdx = 0;
    double xVal, yVal, zVal;
    while (i < m*n)
    {
        fhandle >> xVal >> yVal >> zVal;

        //fill X (only needed for first n lines)
        xIdx = i % n;
        if(i < n)
            (*x)[xIdx] = xVal;

        //fill Y (only needed every m lines)
        yIdx = m - 1 - (i - (i%n))/n;
        if( (i % m) == 1 )
            (*y)[yIdx] = yVal;

        //fill Z
        (*z)[yIdx][xIdx] = zVal;

        ++i;
    }

    return true;
}

}// end aasoni

