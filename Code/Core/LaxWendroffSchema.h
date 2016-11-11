#ifndef __H_LAX_WENDROFF_SCHEMA
#define __H_LAX_WENDROFF_SCHEMA

#include <vector>

#include "AbstractSchema.h"

/**
 * Implementaion of Lax-Wendroff method.
 * @see AbstractSchema
 * Provides all methods that have to be used by discretizator.
 * @author Mateusz Gasior
 */
class LaxWendroffSchema : public AbstractSchema
{
public:

	/**
	* Explicitly defined constructor.
	* @param a Acceleration.
	* @param dx Delta x.
	* @param dt Delta t.
	*/
	LaxWendroffSchema(double a, double dx, double dt)
		: AbstractSchema(a, dx, dt)
	{

	}

	/**
	 * Checks the stability condition for given parameters.
	 * @throw StabilityConditionException if calculated coefficient (CFL) is greater than 1.0.
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
};

#endif
