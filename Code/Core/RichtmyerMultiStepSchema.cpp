/**
 * @file RichtmyerMultiStepSchema.cpp
 * @brief Implementation of methods for RichtmyerMultiStepSchema.
 */

#include "RichtmyerMultiStepSchema.h"

double RichtmyerMultiStepSchema::correctionAtTimeStepHalf(std::vector<double>* previousWave, unsigned int i)
{
	return 0.5 * (previousWave->at(i + 1) + previousWave->at(i - 1))
		- ((this->accelertaion * this->deltaT) / (4 * this->deltaX)) * (previousWave->at(i + 1) - previousWave->at(i - 1));
}

RichtmyerMultiStepSchema::RichtmyerMultiStepSchema(double a, double dx, double dt)
	: AbstractSchema(a, dx, dt)
{

}

void RichtmyerMultiStepSchema::checkStabilityCondition()
{
	double coefficient = this->accelertaion * this->deltaT / this->deltaX;

	if (coefficient > 2.0)
	{
		throw StabilityConditionException();
	}
}

std::vector<double>* RichtmyerMultiStepSchema::apply(std::vector<double>* previousWave)
{
	unsigned int gridSize = previousWave->size();

	std::vector<double> * currentWave = new std::vector<double>(gridSize);

	currentWave->at(0) = previousWave->at(0);
	currentWave->at(1) = previousWave->at(1);
	currentWave->at(gridSize - 2) = previousWave->at(gridSize - 2);
	currentWave->at(gridSize - 1) = previousWave->at(gridSize - 1);

	for (unsigned int i = 2; i < gridSize - 2; i++)
	{
		currentWave->at(i) = previousWave->at(i) - ((this->accelertaion * this->deltaT) / (2 * this->deltaX))
			* (correctionAtTimeStepHalf(previousWave, i + 1) - correctionAtTimeStepHalf(previousWave, i - 1));
	}

	return currentWave;
}
