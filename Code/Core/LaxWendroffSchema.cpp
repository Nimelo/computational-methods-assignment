/**
 * @file LaxWendroffSchema.cpp
 * @brief Implementation of methods for LaxWendroffSchema.
 */
 
#include "LaxWendroffSchema.h"

LaxWendroffSchema::LaxWendroffSchema(double a, double dx, double dt)
	: AbstractSchema(a, dx, dt)
{

}

void LaxWendroffSchema::checkStabilityCondition()
{
	double coefficient = this->accelertaion * this->deltaT / this->deltaX;

	if (coefficient > 1.0)
	{
		throw StabilityConditionException();
	}
}

std::vector<double>* LaxWendroffSchema::apply(std::vector<double>* previousWave)
{
	unsigned int gridSize = previousWave->size();

	std::vector<double> * currentWave = new std::vector<double>(gridSize);

	currentWave->at(0) = previousWave->at(0);
	currentWave->at(gridSize - 1) = previousWave->at(gridSize - 1);

	for (unsigned int i = 1; i < gridSize - 1; i++)
	{
		currentWave->at(i) = previousWave->at(i)
			- this->accelertaion * this->deltaT * ((previousWave->at(i + 1) - previousWave->at(i - 1)) / (2 * this->deltaX))
			+ 0.5 * this->accelertaion * this->accelertaion * this->deltaT * this->deltaT * ((previousWave->at(i + 1) - 2 * previousWave->at(i) + previousWave->at(i - 1)) / (this->deltaX * this->deltaX));
	}

	return currentWave;
}
