#include "Discretizator.h"
#include "WavePoints.h"
#include "Exception.h"
#include <algorithm>

WavePoints * Discretizator::getAnalyticalWave(double time) const
{
	double lb = this->parameters->lowerBound;
	double ub = this->parameters->upperBound;
	double dx = this->parameters->deltaX;
	unsigned int gridSize = this->parameters->meshSize;
	WavePoints * wave = new WavePoints(gridSize);

	for (unsigned int i = 0; i < (unsigned int)gridSize; i++)
	{
		wave->at(i) = this->parameters->analyticalFunction(lb + i * dx, time);
	}

	return wave;
}

void Discretizator::checkStabilityCondition() const
{
	double acceleration = this->parameters->acceleration;
	double dt = this->parameters->deltaT;
	double dx = this->parameters->deltaX;
	this->parameters->schema->checkStabilityCondition(acceleration, dx, dt);
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
	WavePoints * previousWave = getAnalyticalWave(time);

	while (timeLevels.size() > 0)
	{
		while (time < timeLevels.at(0))
		{
			try {
				WavePoints * currentWave = this->parameters->schema->apply(previousWave, this->parameters->deltaX, this->parameters->deltaT, this->parameters->acceleration);
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

		result->addWaves(time - this->parameters->deltaT, new WavePoints(*previousWave), getAnalyticalWave(time));
		timeLevels.erase(timeLevels.begin());
	}
	
	delete previousWave;
	return result;
}
