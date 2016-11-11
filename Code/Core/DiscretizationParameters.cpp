#include "DiscretizationParameters.h"

DiscretizationParameters::DiscretizationParameters(double lowerBound, double upperBound,
	double acceleration, double(*analyticalFunction)(double, double), 
	AbstractSchema * schema, unsigned int meshSize, 
	std::vector<double> timeLevels, double dt)
	: lowerBound(lowerBound), upperBound(upperBound),
	acceleration(acceleration), analyticalFunction(analyticalFunction), schema(schema),
	meshSize(meshSize), timeLevels(timeLevels),
	deltaT(dt)
{
	this->deltaX = calculateDeltaX();
}

DiscretizationParameters::~DiscretizationParameters()
{
	delete schema;
}

double DiscretizationParameters::calculateDeltaX() const
{
	return (this->upperBound - this->lowerBound) / this->meshSize;
}
