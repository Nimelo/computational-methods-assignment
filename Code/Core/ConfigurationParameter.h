#ifndef __H_PARAMETER
#define __H_PARAMETER

#include <string>
#include <sstream>
#include <stdexcept>
#include <vector>

#include "AnalyticalFunctionsEnum.h"
#include "SchemasEnum.h"

/**
 * ConfigurationParameter provides bunch of overloaded cast operators.
 * It is used in order to cast generic string value of parameter to more complex types.
 * @author Mateusz Gasior
 */
struct ConfigurationParameter
{
	/**
	 * Value stored as string.
	 */
	std::string value;

	/**
	 * Overloaded generic cast operator.
	 * @param <T> Generic typename.
	 * @throws std::runtime_error if conversion cannot be performed using std::stringstream.
	 */
	double toDouble()
	{
		std::stringstream ss(value);
		double convertedValue;
		if (std::stringstream(value) >> convertedValue)
			return convertedValue;
		else
			throw std::runtime_error("Conversion failed");
	}

	unsigned int toUnsignedInt()
	{
		std::stringstream ss(value);
		double convertedValue;
		if (std::stringstream(value) >> convertedValue)
			return convertedValue;
		else
			throw std::runtime_error("Conversion failed");
	}

	std::vector<double> toVectorOfDouble()
	{
		std::stringstream ss(value);
		std::vector<double> returnValue;
		std::string token;
		double convertedValue;
		while (std::getline(ss, token, ',')) {
			if (std::stringstream(token) >> convertedValue)
				returnValue.push_back(convertedValue);
			else
				throw std::runtime_error("Conversion failed");
		}

		return returnValue;
	}

	/**
	 * Specialized overloaded cast operator for AnalyticalFunctionEnum.
	 * @see AnalyticalFunctionEnum
	 * Correct values are: "exp" for EXP_FUNCTION and "sign" for SIGN_FUNCTION.
	 * @throws std::runtime_error if value to convert is not in a set of correct values.
	 */
	AnalyticalFunctionEnum toAnalyticalFunction()
	{
		if (value == "exp")
		{
			return EXP_FUNCTION;
		}
		else if (value == "sign")
		{
			return SIGN_FUNCTION;
		}
		else
			throw std::runtime_error("Conversion failed");
	}
	/**
	 * Specialized overloaded cast operator for SchemasEnum.
	 * @see SchemasEnum
	 * Correct values are: "upwind_implicit" for UPWIND_IMPLICIT,
	 *                     "upwind_explicit" for UPWIND_EXPLICIT,
	 *                     "lax-wendroff" for LAX_WENDROFF and
	 *					   "richtmyer-ms" for RICHTMYER_MULTI_STEP.
	 * @throws std::runtime_error if value to convert is not in a set of correct values.
	 */
	SchemasEnum toSchema()
	{
		if (value == "upwind_implicit")
		{
			return UPWIND_IMPLICIT;
		}
		else if (value == "upwind_explicit")
		{
			return UPWIND_EXPLICIT;
		}
		else if (value == "lax-wendroff")
		{
			return LAX_WENDROFF;
		}
		else if (value == "richtmyer-ms")
		{
			return RICHTMYER_MULTI_STEP;
		}
		else
			throw std::runtime_error("Conversion failed");
	}
};

#endif
