#ifndef __H_DISCRETIZATOR
#define __H_DISCRETIZATOR

#include "DiscretizationParameters.h"
#include "DiscretizationResult.h"

/**
 * Tool for solving discretization problem given by parameters.
 * @author Mateusz Gasior
 */
class Discretizator
{
private:

	/**
	 * Parameters for discretization.
	 */
	DiscretizationParameters * parameters;

	/**
	 * Return analytical wave for given time.
	 * @param time Time for calculating analytical wave.
	 * @return Analytical wave for given time.
	 */
	WavePoints * getAnalyticalWave(double time) const;

	/**
	 * Invokes stability condition function from schema that is in parameters.
	 * @throw StabilityConditionException if calculated coefficient (CFL) makes schema unstable. 
	 */
	void checkStabilityCondition() const;
public:

	/**
	 * Overridden constructor for explicitly given parameters.
	 * @param parameters Discretization parameters.
	 */
	Discretizator(DiscretizationParameters * parameters);

	/**
	 * Default destructor.
	 */
	~Discretizator();
	
	/**
	 * Performs discretization process for given parameters and produces result.
	 * @return Result of discretization.
	 */
	DiscretizationResult * discretize();
};

#endif