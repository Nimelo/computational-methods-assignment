#ifndef __H_ABSTRACT_ANALYTICAL_FUNCTIONS_RESOLVER
#define __H_ABSTRACT_ANALYTICAL_FUNCTIONS_RESOLVER

#include <functional>
#include "AnalyticalFunctionsEnum.h"

/**
 * Abstraction for resolving analytical function for discretization. 
 * @author Mateusz Gasior
 */
class AbstractAnalyticalFunctionsResolver
{
public:
	/**
	 * Resolves analytical function by given key.
	 * @see AnalyticalFunctionEnum
	 * @param key Key for analytical function.
	 * @return Analytical function corresponding to the given key.
	 */
	virtual std::function<double(double, double)> resolve(AnalyticalFunctionEnum key) = 0;
};

#endif