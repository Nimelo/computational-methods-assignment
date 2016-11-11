#ifndef __H_RICHTMYER_MULTI_STEP_SCHEMA
#define __H_RICHTMYER_MULTI_STEP_SCHEMA

#include <vector>

#include "AbstractSchema.h"
#include "StabilityConditionException.h"

/**
 * Implementaion of Richtmyer multi-step method.
 * @see AbstractSchema
 * Provides all methods that have to be used by discretizator.
 * @author Mateusz Gasior
 */
class RichtmyerMultiStepSchema : public AbstractSchema
{
private:
	/**
	 * Calculates partial solution for time step n + half.
	 * @param previousWave wave for which is performed calculations.
	 * @param i Index for which point calculations are made.
	 */
	double correctionAtTimeStepHalf(std::vector<double> * previousWave, unsigned int i)
	{
		return 0.5 * (previousWave->at(i + 1) + previousWave->at(i - 1))
			- ((this->accelertaion * this->deltaT) / (4 * this->deltaX)) * (previousWave->at(i + 1) - previousWave->at(i - 1));
	}
public:
	/**
	* Explicitly defined constructor.
	* @param a Acceleration.
	* @param dx Delta x.
	* @param dt Delta t.
	*/
	RichtmyerMultiStepSchema(double a, double dx, double dt)
		: AbstractSchema(a, dx, dt)
	{

	}

	/**
	 * Checks the stability condition for given parameters.
	 * @throw StabilityConditionException if calculated coefficient (CFL) is greater than 2.0.
	 */
	void checkStabilityCondition()
	{
		double coefficient = this->accelertaion * this->deltaT / this->deltaX;

		if (coefficient > 2.0)
		{
			throw StabilityConditionException();
		}
	}
	
	/**
	 * Applies schema for wave and given parameters.
	 * @param previousWave previousWave that is base for next time step discretization.
	 * @return Wave for next time step.
	 */
	std::vector<double> * apply(std::vector<double> * previousWave)
	{
		unsigned int gridSize = previousWave->size();

		std::vector<double> * currentWave = new std::vector<double>(gridSize);

		//inny schemat
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
};

#endif
