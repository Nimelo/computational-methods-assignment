#include "DiscretizationParameters.h"

DiscretizationParameters::DiscretizationParameters(double lowerBound, double upperBound, 
	double acceleration, std::function<double(double, double)> analyticalFunction, AbstractSchema * schema,
	unsigned int meshSize, std::vector<double> timeLevels,
	double dt, double dx)
	: lowerBound(lowerBound), upperBound(upperBound),
	acceleration(acceleration), analyticalFunction(analyticalFunction), schema(schema),
	meshSize(meshSize), timeLevels(timeLevels),
	deltaT(dt), deltaX(dx)
{
}

DiscretizationParameters::DiscretizationParameters(AbstractSchema * schema, std::function<double(double, double)> analyticalFunction,
	Configuration * configuration, double dt)
{
	this->lowerBound = configuration->lowerBound;
	this->upperBound = configuration->upperBound;
	this->acceleration = configuration->acceleration;
	this->schema = schema;
	this->analyticalFunction = analyticalFunction;
	this->meshSize = configuration->meshSize;
	this->timeLevels = configuration->timeLevels;
	this->deltaT = dt;

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
