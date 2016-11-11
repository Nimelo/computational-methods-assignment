#ifndef __H_UPWIND_EXPLICIT_SCHEMA
#define __H_UPWIND_EXPLICIT_SCHEMA

#include <vector>

#include "AbstractSchema.h"
#include "StabilityConditionException.h"

/**
 * Implementaion of upwind explicit method.
 * @see AbstractSchema
 * Provides all methods that have to be used by discretizator.
 * @author Mateusz Gasior
 */
class UpwindExplicitSchema : public AbstractSchema
{
public:
	/**
	* Explicitly defined constructor.
	* @param a Acceleration.
	* @param dx Delta x.
	* @param dt Delta t.
	*/
	UpwindExplicitSchema(double a, double dx, double dt)
		: AbstractSchema(a, dx, dt)
	{

	}

	/**
	 * Checks the stability condition for given parameters.
	 * @throw StabilityConditionException if calculated coefficient (CFL) is greater than upper boundary.
	 */
	void checkStabilityCondition()
	{
		double coefficient = this->accelertaion * this->deltaT / this->deltaX;
		if (coefficient > 1.0)
		{
			throw StabilityConditionException("Schema is unstable!");
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
		double coefficient = this->accelertaion * (this->deltaT / this->deltaX);

		std::vector<double> * currentWave = new std::vector<double>(gridSize);
		
		currentWave->at(0) = previousWave->at(0);
		currentWave->at(gridSize - 1) = previousWave->at(gridSize - 1);

		for (unsigned int i = 1; i < gridSize - 1; i++)
		{
			currentWave->at(i) = previousWave->at(i) - coefficient * (previousWave->at(i) - previousWave->at(i - 1));
		}

		return currentWave;
	}
};

#endif
