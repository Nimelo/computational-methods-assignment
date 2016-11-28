#ifndef __H_UPWIND_IMPLICIT_SCHEMA
#define __H_UPWIND_IMPLICIT_SCHEMA

#include <vector>
#include <algorithm>

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

		if (coefficient == 0)
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

		double cfl = this->accelertaion * this->deltaT / this->deltaX;

		currentWave->at(0) = previousWave->at(0);
		currentWave->at(gridSize - 1) = previousWave->at(gridSize - 1);

		if (cfl > 0)
		{
			for (unsigned int i = 1; i < gridSize - 1; i++)
			{
				currentWave->at(i) = (previousWave->at(i) + cfl * currentWave->at(i - 1)) / (1.0 + cfl);
			}
		}
		else
		{
			for (unsigned int i = gridSize - 1; i >= 2; i--)
			{
				currentWave->at(i - 1) = ((1.0 + cfl) * currentWave->at(i) - previousWave->at(i)) / cfl;
			}
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

	/**
	 * Shifts wave by 2uT
	 * @param previousWave wave for which post action will be applied.
	 * @param t Current time.
	 * @return Adjusted wave.
	 */
	virtual std::vector<double> * postApplyAction(std::vector<double> * previousWave, double t)
	{
		double coefficient = (this->accelertaion * this->deltaT) / this->deltaX;
		if (coefficient < 0)
		{
			unsigned int offset = 2 * (1.0 / this->deltaX) * -1 * this->accelertaion * t;

			for (unsigned int i = 0; i < offset; i++)
			{
				for (unsigned int j = previousWave->size() - 1; j >= 1; j--)
				{
					(*previousWave)[j] = (*previousWave)[j-1];
				}
			}
			//std::rotate(previousWave->rbegin(), previousWave->rbegin() + offset, previousWave->rend());
		}
		
		return previousWave;
	}
};

#endif
