#include "Configuration.h"

Configuration::Configuration(double lowerBound, double upperBound, 
	double acceleration, AnalyticalFunctionEnum analyticalFunction, SchemasEnum schema,
	unsigned int meshSize, std::vector<double> timeLevels, double deltaT)
	: lowerBound(lowerBound), upperBound(upperBound),
	acceleration(acceleration), analyticalFunction(analyticalFunction),
	meshSize(meshSize), timeLevels(timeLevels), deltaT(deltaT), schema(schema)
{
}
