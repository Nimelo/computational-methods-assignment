#ifndef __H_UPWIND_IMPLICIT_SCHEMA
#define __H_UPWIND_IMPLICIT_SCHEMA

#include <vector>

#include "AbstractSchema.h"
#include "StabilityConditionException.h"
#include "ZeroPivotException.h"

/**
 * Implementaion of upwind implicit method.
 * @see AbstractSchema
 * Provides all methods that have to be used by discretizator.
 * Stores calculated matrices for increasing performance.
 * @author Mateusz Gasior
 */
class UpwindImplicitSchema : public AbstractSchema
{
public:

	/**
	* Checks the stability condition for given parameters.
	* @throw StabilityConditionException if calculated coefficient (CFL) is negative.
	*/
	void checkStabilityCondition()
	{
		double coefficient = (this->accelertaion * this->deltaT) / this->deltaX;

		if (coefficient <= 0)
			throw StabilityConditionException();
	}

	/**
	* Applies schema for wave and given parameters.
	* @param previousWave previousWave that is base for next time step discretization.
	* @param dx Delta x.
	* @param dt Delta t.
	* @param a Acceleration.
	* @return Wave for next time step.
	*/
	std::vector<double> * apply(std::vector<double> * previousWave)
	{
		unsigned int gridSize = previousWave->size();

		std::vector<double> * currentWave = new std::vector<double>(gridSize);

		currentWave->at(0) = previousWave->at(0);
		currentWave->at(gridSize - 1) = previousWave->at(gridSize - 1);

		double coefficient = this->accelertaion * this->deltaT / this->deltaX;

		for (unsigned int i = 1; i < gridSize - 1; i++)
		{
			currentWave->at(i) = (previousWave->at(i) + coefficient * previousWave->at(i - 1)) / (1.0 + coefficient);
		}

		return currentWave;
	}

	/**
	* Explicitly defined constructor.
	* @param a Acceleration.
	* @param dx Delta x.
	* @param dt Delta t.
	*/
	UpwindImplicitSchema(double a, double dx, double dt)
		: AbstractSchema(a, dx, dt)
	{
	}
};

#endif
