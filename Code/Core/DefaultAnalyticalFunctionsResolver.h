#ifndef __H_DEFAULT_ANALYTICAL_FUNCTIONS_RESOLVER
#define __H_DEFAULT_ANALYTICAL_FUNCTIONS_RESOLVER

#include <functional>
#include "AnalyticalFunctionsEnum.h"
#include "AnalyticalFunctions.h"

#include "AbstractAnalyticalFunctionsResolver.h"

/**
 * Default class for resolving analytical function for discretization.
 * @see AbstractAnalyticalFunctionsResolver
 * @author Mateusz Gasior
 */
class DefaultAnalyticalFunctionsResolver : public AbstractAnalyticalFunctionsResolver
{
public:
	/**
	 * Resolves analytical function by given key.
	 * @see AnalyticalFunctionEnum
	 * @param key Key for analytical function.
	 * @return Analytical function corresponding to the given key.
	 */
	std::function<double(double, double)> resolve(AnalyticalFunctionEnum key)
	{
		switch (key)	
		{
		case SIGN_FUNCTION:
			return AnalyticalFunctions::signFunction;
		case EXP_FUNCTION:
			return AnalyticalFunctions::expFunction;
		}
	};
};

#endif
