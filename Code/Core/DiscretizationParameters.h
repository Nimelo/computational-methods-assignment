#ifndef __H_DISCRETIZATION_PARAMETERS
#define __H_DISCRETIZATION_PARAMETERS

#include <functional>
#include <vector>

#include "Configuration.h"
#include "AbstractSchema.h"
#include "AbstractAnalyticalFunctionsResolver.h"
#include "AbstractSchemasResolver.h"

/**
 * Stores values needed to perform discretization.
 */
struct DiscretizationParameters
{
	/**
	 * Lower bound.
	 */
	double lowerBound;

	/**
	 * Upper bound.
	 */
	double upperBound;

	/**
	 * Acceleration.
	 */
	double acceleration;

	/**
	 * Analytical function.
	 */
	std::function<double(double, double)> analyticalFunction;

	/**
	 * Schema.
	 */
	AbstractSchema * schema;

	/**
	 * Mesh size (grid size).
	 */
	unsigned int meshSize;

	/**
	 * Time levels.
	 */
	std::vector<double> timeLevels;

	/**
	 * Delta t.
	 */
	double deltaT;

	/**
	 * Delta x.
     */
	double deltaX;

	/**
	 * Calculates delta x based on current lower, upper bounds and mesh size.
	 * Sets deltaX to new value.
	 * @return Calculated delta x.
	 */
	double calculateDeltaX() const;


	/**
	 * Overloaded constructor for explicitly given parameters.
	 * @param lowerBound Lower bound.
	 * @param upperBound Upper bound.
	 * @param acceleration Acceleration.
	 * @param analyticalFunction Analytical function.
	 * @param schema Schema.
	 * @param meshSize Mesh size (grid size).
	 * @param timeLevels Time levels.
	 * @param dt Delta t.
	 * @param dx Delta x.
	 */
	DiscretizationParameters(double lowerBound, double upperBound,
		double acceleration, std::function<double(double, double)> analyticalFunction,
		AbstractSchema * schema, unsigned int meshSize, std::vector<double> timeLevels,
		double dt, double dx);

	/**
	 * Overloaded constructor that bases on Configuration.
	 * All the fields specified 
	 * @see Configuration
     * @configuration configuration Configuration for most of the parameters.
	 * @param analyticalFunction Analytical function.
	 * @param schema Schema.
	 * @param dt Delta t.
	*/
	DiscretizationParameters(AbstractSchema * schema, std::function<double(double, double)> analyticalFunction,
		Configuration * configuration, double dt);

	/**
	 * Default destructor.
	 */
	~DiscretizationParameters();
};

#endif
