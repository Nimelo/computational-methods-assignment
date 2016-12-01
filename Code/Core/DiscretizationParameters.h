/**
 * @file DiscretizationParameters.h
 * @brief Declaration of methods for DiscretizationParameters.
 */
#ifndef __H_DISCRETIZATION_PARAMETERS
#define __H_DISCRETIZATION_PARAMETERS

#include <vector>

#include "AbstractSchema.h"

/**
 * @brief Stores values needed to perform discretization.
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
	double (*analyticalFunction) (double, double);

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
	 */
	DiscretizationParameters(double lowerBound, double upperBound,
		double acceleration, double(*analyticalFunction) (double, double),
		AbstractSchema * schema, unsigned int meshSize, std::vector<double> timeLevels,
		double dt);

	/**
	 * Default destructor.
	 */
	~DiscretizationParameters();
};

#endif
