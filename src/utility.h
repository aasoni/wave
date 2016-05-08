#ifndef UTILITY_H
#define UTILITY_H

#include <vector>

using namespace std;

namespace aasoni {

typedef vector<double> VEC;
typedef vector<VEC> MAT;

void bathymetryToHeight(MAT *b);

void heightAndBathymetryToSurface(MAT *output,
                                  const MAT &bathymetry,
                                  const MAT &height);

bool epsEqual(double a, double b);

}

#endif
