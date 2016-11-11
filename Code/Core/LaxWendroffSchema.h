#ifndef __H_LAX_WENDROFF_SCHEMA
#define __H_LAX_WENDROFF_SCHEMA

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
	 * Checks the stability condition for given parameters.
	 * @param a Acceleration.
	 * @param dx Delta x.
	 * @param dt Delta t.
	 * @throw StabilityConditionException if calculated coefficient (CFL) is greater than 1.0.
	 */
	void checkStabilityCondition(double a, double dx, double dt)
	{
		double coefficient = a * dt / dx;
		if (coefficient > 1.0)
		{
			throw StabilityConditionException("Schema is unstable!");
		}
	}

	/**
	 * Applies schema for wave and given parameters.
	 * @param previousWave previousWave that is base for next time step discretization.
	 * @param dx Delta x.
	 * @param dt Delta t.
	 * @param a Acceleration.
	 * @return Wave for next time step.
	 */
	WavePoints * apply(WavePoints * previousWave, double dx, double dt, double a)
	{
		unsigned int gridSize = previousWave->size();

		WavePoints * currentWave = new WavePoints(gridSize);

		currentWave->at(0) = previousWave->at(0);
		currentWave->at(gridSize - 1) = previousWave->at(gridSize - 1);

		for (unsigned int i = 1; i < gridSize - 1; i++)
		{
			currentWave->at(i) = previousWave->at(i)
				- a * dt * ((previousWave->at(i + 1) - previousWave->at(i - 1)) / (2 * dx))
					+ 0.5 * a * a * dt * dt * ((previousWave->at(i + 1) - 2 * previousWave->at(i) + previousWave->at(i - 1)) / (dx * dx));
		}

		return currentWave;
	}
};

#endif
