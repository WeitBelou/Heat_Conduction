#include "./layer.h"
#include <QVector>
#include <exception>
#include <iostream>
#include "./argument.h"
using namespace std;
// (lmbd) lambda for heat capacity, p for density, c for thermal conductivity
ArgumentForDraw calculateAllLayers(ArgumentForCalc const & argument);
