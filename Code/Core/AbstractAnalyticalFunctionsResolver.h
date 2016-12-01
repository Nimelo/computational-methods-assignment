/**
* @file AbstractAnalyticalFunctionsResolver.h
* @brief Declaration of methods for AbstractAnalyticalFunctionsResolver.
*/
#ifndef __H_ABSTRACT_ANALYTICAL_FUNCTIONS_RESOLVER
#define __H_ABSTRACT_ANALYTICAL_FUNCTIONS_RESOLVER

#include "AnalyticalFunctionsEnum.h"

/**
 * @brief Abstraction for resolving analytical function for discretization. 
 * @author Mateusz Gasior
 */
class AbstractAnalyticalFunctionsResolver
{
public:
	typedef double(*AnalyticalFunctionType) (double, double);

	/**
	 * Resolves analytical function by given key.
	 * @see AnalyticalFunctionEnum
	 * @param key Key for analytical function.
	 * @return Analytical function corresponding to the given key.
	 */
	virtual AnalyticalFunctionType resolve(AnalyticalFunctionEnum key) = 0;
};

#endif