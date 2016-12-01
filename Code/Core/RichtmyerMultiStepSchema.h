/**
 * @file RichtmyerMultiStepSchema.h
 * @brief Declaration of methods for RichtmyerMultiStepSchema.
 */

#ifndef __H_RICHTMYER_MULTI_STEP_SCHEMA
#define __H_RICHTMYER_MULTI_STEP_SCHEMA

#include <vector>

#include "AbstractSchema.h"
#include "StabilityConditionException.h"

/**
 * @brief Implementaion of Richtmyer multi-step method.
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
	double correctionAtTimeStepHalf(std::vector<double> * previousWave, unsigned int i);
public:
	/**
	* Explicitly defined constructor.
	* @param a Acceleration.
	* @param dx Delta x.
	* @param dt Delta t.
	*/
	RichtmyerMultiStepSchema(double a, double dx, double dt);

	/**
	 * Checks the stability condition for given parameters.
	 * @throw StabilityConditionException if calculated coefficient (CFL) is greater than 2.0.
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
