/**
* @file Configuration.cpp
* @brief Implementation of methods for Configuration.
*/
#include "Configuration.h"

Configuration::Configuration(double lowerBound, double upperBound,
	double acceleration, AnalyticalFunctionEnum analyticalFunction, SchemasEnum schema,
	unsigned int meshSize, std::vector<double> timeLevels, double deltaT)
	: lowerBound(lowerBound), upperBound(upperBound),
	acceleration(acceleration), analyticalFunction(analyticalFunction),
	meshSize(meshSize), timeLevels(timeLevels), deltaT(deltaT),
	searchOptimalDeltaT(false), schema(schema)
{
}

Configuration::Configuration(double lowerBound, double upperBound,
	double acceleration, AnalyticalFunctionEnum analyticalFunction, SchemasEnum schema,
	unsigned int meshSize, std::vector<double> timeLevels,
	bool searchOptimalT, double deltaT,
	double minDeltaT, double maxDeltaT, double deltaTStep)
	: lowerBound(lowerBound), upperBound(upperBound),
	acceleration(acceleration), analyticalFunction(analyticalFunction),
	meshSize(meshSize), timeLevels(timeLevels),
	deltaT(deltaT), searchOptimalDeltaT(searchOptimalT),
	minDeltaT(minDeltaT), maxDeltaT(maxDeltaT),
	deltaTStep(deltaTStep), schema(schema)
{
}
