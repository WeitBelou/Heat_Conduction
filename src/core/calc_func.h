#include "./layer.h"
#include <vector>
#include <exception>
#include <iostream>
using namespace std;
// (lmbd) lambda for heat capacity, p for density, c for thermal conductivity
vector <Layer> calculateAllLayers( const Layer  & zeroLayer, const BoolNet & idNet,
						  int tMax, double tStep, double xStep, double yStep,
						  double p, double lmbd, double c);
