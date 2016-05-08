#include <xyz_writer.h>

#include <fstream>
#include <iostream>
#include <math.h>

namespace aasoni {
   
//writes file in format:
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
bool XYZ_Writer::writeToFile(const VEC &x,
                             const VEC &y, 
                             const vector<VEC> &z,
                             const string &fileName)
{
    ofstream fhandle(fileName, ios::out);

    //get size from vectors
    size_t n = x.size();
    size_t m = y.size();

    double xVal, yVal, zVal;
    size_t xIdx, yIdx;
    for(size_t i = 0; i != m*n; ++i)
    {
        //write x value
        xIdx = i % n;
        xVal = x[xIdx];
        fhandle << xVal << " ";

        //write y value
        yIdx = m - 1 - (i - (i%n))/n;
        yVal = y[yIdx];
        fhandle << yVal << " ";

        //write z value
        zVal = isnan(z[yIdx][xIdx]) ? 1.0 : z[yIdx][xIdx];


        fhandle << zVal << endl;
    }

    return true;
}

}// end aasoni

