#ifndef __H_CONFIGURATION
#define __H_CONFIGURATION

#include <vector>
#include "SchemasEnum.h"
#include "AnalyticalFunctionsEnum.h"

/**
 * Stores information about all parameters used during discretization process, such as types and numeric values.
 * @author Mateusz Gasior
 */
struct Configuration
{	
	/**
	 * Lower boundary.
	 */
	double lowerBound;

	/**
	 * Upper boundary.
	 */
	double upperBound;

	/**
	 * Acceleration for advection function.
	 */
	double acceleration;

	/**
	 * Analytical function enumerator for comparising results and generating initial values.
	 * @see AnalyticalFunctionEnum
	 */
	AnalyticalFunctionEnum analyticalFunction;

	/**
	 * Schema enumerator that is used in disretization process.
	 * @see SchemasEnum
	 */
	SchemasEnum schema;

	/**
	 * Mesh size (grid size).
	 */
	unsigned int meshSize;

	/**
	 * Time levels for which there should be performed additional actions, such as calculation of norms and printing to file.
	 */
	std::vector<double> timeLevels;

	/**
	 * Value of delta T.
	 * It's used only if searchOptimalDeltaT is set to false.
	 */
	double deltaT;

	/**
	* Flag indicates if during calculation. Program should search for optimal value of delta t.
	*/
	bool searchOptimalDeltaT;

	/**
	* Value of minimum delta T.
	* Optimalization process starts with this value.
	* It's used only if searchOptimalDeltaT is set to false.
	*/
	double minDeltaT;

	/**
	* Value of maximum delta T.
	* Optimalization process ends with this value.
	* It's used only if searchOptimalDeltaT is set to false.
	*/
	double maxDeltaT;

	/**
	* Value of step of delta t.
	* During optimalization process current delta t is incrised by this value.
	* It's used only if searchOptimalDeltaT is set to false.
	*/
	double deltaTStep;

	/**
	* Overloaded constructor for Configuration with specified delta t.
	* @param lowerBound Lower boundary.
	* @param upperBound Upper boundary.
	* @param acceleration Acceleration.
	* @param analyticalFunction Analytical function enumerator.
	* @param schema Schema enumerator.
	* @param meshSize Mesh size.
	* @param timeLevels Time levels.
	* @param deltaT Delta t.
	*/
	Configuration(double lowerBound, double upperBound, double acceleration,
		AnalyticalFunctionEnum analyticalFunction, SchemasEnum schema, unsigned int meshSize,
		std::vector<double> timeLevels, double deltaT);

	/**
	* Overloaded constructor for Configuration for explicitly given parameters.
	* @param lowerBound Lower boundary.
	* @param upperBound Upper boundary.
	* @param acceleration Acceleration.
	* @param analyticalFunction Analytical function enumerator.
	* @param schema Schema enumerator.
	* @param meshSize Mesh size.
	* @param timeLevels Time levels.
	* @param searchOptimalT Flag indicates searching of optimal delta t.
	* @param deltaT Delta t.
	* @param minDeltaT Minimum delta t.
	* @param maxDeltaT Maximum delta t.
	* @param deltaTStep Delta t step.
	*/
	Configuration(double lowerBound, double upperBound,
		double acceleration, AnalyticalFunctionEnum analyticalFunction, SchemasEnum schema,
		unsigned int meshSize, std::vector<double> timeLevels,
		bool searchOptimalT, double deltaT,
		double minDeltaT, double maxDeltaT, double deltaTStep);
};
#endif
