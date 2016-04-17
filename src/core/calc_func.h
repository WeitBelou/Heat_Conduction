#include "./layer.h"

// (lmbd) lambda for heat capacity, p for density, c for thermal conductivity
Layer* calculateAllLayers(const Layer & zeroLayer,  const BoolNet & idNet,
						  double tMax,  double tStep, double xStep,
						  double yStep,  double & p, double lmbd, double c);
