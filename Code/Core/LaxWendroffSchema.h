/**
 * @file LaxWendroffSchema.h
 * @brief Declaration of methods for LaxWendroffSchema.
 */

#ifndef __H_LAX_WENDROFF_SCHEMA
#define __H_LAX_WENDROFF_SCHEMA

#include <vector>

#include "AbstractSchema.h"
#include "StabilityConditionException.h"

/**
 * @brief Implementaion of Lax-Wendroff method.
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
	LaxWendroffSchema(double a, double dx, double dt);

	/**
	 * Checks the stability condition for given parameters.
	 * @throw StabilityConditionException if calculated coefficient (CFL) is greater than 1.0.
	 */
	void checkStabilityCondition();

	/**
	 * Applies schema for wave and given parameters.
	 * @param previousWave previousWave that is base for next time step discretization.
	 * @return Wave for next time step.
	 */
	std::vector<double> * apply(std::vector<double> * previousWave);
};

#endif
