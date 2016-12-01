/**
 * @file DefaultAnalyticalFunctionsResolver.h
 * @brief Declaration of methods for DefaultAnalyticalFunctionsResolver.
 */

#ifndef __H_DEFAULT_ANALYTICAL_FUNCTIONS_RESOLVER
#define __H_DEFAULT_ANALYTICAL_FUNCTIONS_RESOLVER

#include "AbstractAnalyticalFunctionsResolver.h"

#include "AnalyticalFunctionsEnum.h"
#include "AnalyticalFunctions.h"

/**
 * @brief Default class for resolving analytical function for discretization.
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
	AnalyticalFunctionType resolve(AnalyticalFunctionEnum key)
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
