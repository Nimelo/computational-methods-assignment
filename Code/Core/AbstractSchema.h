#ifndef __H_ABSTRACT_SCHEMA
#define __H_ABSTRACT_SCHEMA

#include "WavePoints.h"

/**
 * Abstraction for schema.
 * Provides all methods that have to be used by discretizator.
 * @author Mateusz Gasior
 */
class AbstractSchema
{
public:

	/**
	 * Default destructor.
	 */
	virtual ~AbstractSchema()
	{

	}

	/**
	 * Checks the stability condition for given parameters.
	 * @param a Acceleration.
	 * @param dx Delta x.
	 * @param dt Delta t.
	 * @throw StabilityConditionException if calculated coefficient (CFL) is greater than upper boundary.
	 */
	virtual void checkStabilityCondition(double a, double dx, double dt) = 0;

	/**
	 * Applies schema for wave and given parameters.
	 * @param previousWave previousWave that is base for next time step discretization.
	 * @param dx Delta x.
	 * @param dt Delta t.
	 * @param a Acceleration.
	 * @return Wave for next time step.
	 */
	virtual WavePoints * apply(WavePoints * previousWave, double dx, double dt, double a) = 0;
};
#endif
