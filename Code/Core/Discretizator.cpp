#include <algorithm>
#include <vector>

#include "Discretizator.h"
#include "WavePoints.h"
#include "Exception.h"

std::vector<double> * Discretizator::getAnalyticalWave(double time) const
{
	double lb = this->parameters->lowerBound;
	double ub = this->parameters->upperBound;
	double dx = this->parameters->deltaX;
	unsigned int gridSize = this->parameters->meshSize;
	std::vector<double> * wave = new std::vector<double>(gridSize);

	for (unsigned int i = 0; i < (unsigned int)gridSize; i++)
	{
		wave->at(i) = this->parameters->analyticalFunction(lb + i * dx, time);
	}

	return wave;
}

void Discretizator::checkStabilityCondition() const
{
	this->parameters->schema->checkStabilityCondition();
}

Discretizator::Discretizator(DiscretizationParameters * parameters)
	: parameters(parameters)
{
}


Discretizator::~Discretizator()
{
	delete this->parameters;
}

DiscretizationResult * Discretizator::discretize()
{
	this->checkStabilityCondition();
	DiscretizationResult * result = new DiscretizationResult(this->parameters->lowerBound, this->parameters->upperBound, this->parameters->deltaX);
	std::sort(this->parameters->timeLevels.begin(), this->parameters->timeLevels.end());

	std::vector<double> timeLevels(this->parameters->timeLevels);

	double time = 0.0;
	std::vector<double> * previousWave = getAnalyticalWave(time);

	while (timeLevels.size() > 0)
	{
		while (time < timeLevels.at(0))
		{
			try {
				std::vector<double> * currentWave = this->parameters->schema->apply(previousWave);
				delete previousWave;
				previousWave = currentWave;
				time += this->parameters->deltaT;
			}
			catch (Exception & e)
			{
				delete previousWave;
				delete result;
				throw e;
			}		
		}

		result->addWaves(time - this->parameters->deltaT, new std::vector<double>(*previousWave), getAnalyticalWave(time));
		timeLevels.erase(timeLevels.begin());
	}
	
	delete previousWave;
	return result;
}
