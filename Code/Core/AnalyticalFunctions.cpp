#include "AnalyticalFunctions.h"
#include <math.h>

double AnalyticalFunctions::sign(double val)
{
	if (val < 0)
		return -1;
	else if (val == 0)
		return 0;
	else
		return 1;
}

double AnalyticalFunctions::expFunction(double x, double t)
{
	return 0.5 * exp(-(x - 1.75 * t) * (x - 1.75 * t));
}

double AnalyticalFunctions::signFunction(double x, double t)
{
	return 0.5 * (sign(x - 1.75 * t) + 1.0);
}
