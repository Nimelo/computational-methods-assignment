#ifndef __H_RICHTMYER_MULTI_STEP_SCHEMA
#define __H_RICHTMYER_MULTI_STEP_SCHEMA

#include "AbstractSchema.h"

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
	 * @param dx Delta x.
	 * @param dt Delta t.
	 * @param a Acceleration.
	 * @param i Index for which point calculations are made.
	 */
	double correctionAtTimeStepHalf(WavePoints * previousWave, double dx, double dt, double a, unsigned int i)
	{
		return 0.5 * (previousWave->at(i + 1) + previousWave->at(i - 1))
			- ((a * dt) / (4 * dx)) * (previousWave->at(i + 1) - previousWave->at(i - 1));
	}
public:

	/**
	 * Checks the stability condition for given parameters.
	 * @param a Acceleration.
	 * @param dx Delta x.
	 * @param dt Delta t.
	 * @throw StabilityConditionException if calculated coefficient (CFL) is greater than 2.0.
	 */
	void checkStabilityCondition(double a, double dx, double dt)
	{
		double coefficient = a * dt / dx;
		if (coefficient > 2.0)
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

		//inny schemat
		currentWave->at(0) = previousWave->at(0);
		currentWave->at(1) = previousWave->at(1);
		currentWave->at(gridSize - 2) = previousWave->at(gridSize - 2);
		currentWave->at(gridSize - 1) = previousWave->at(gridSize - 1);

		for (unsigned int i = 2; i < gridSize - 2; i++)
		{
			currentWave->at(i) = previousWave->at(i) - ((a * dt) / (2 * dx)) 
				* (correctionAtTimeStepHalf(previousWave, dx, dt, a, i + 1) - correctionAtTimeStepHalf(previousWave, dx, dt, a, i - 1));
		}

		return currentWave;
	}
};

#endif
