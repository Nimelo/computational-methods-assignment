/**
 * @file ConfigurationParameter.h
 * @brief Declaration of methods for ConfigurationParameter.
 */
#ifndef __H_PARAMETER
#define __H_PARAMETER

#include <string>
#include <sstream>
#include <stdexcept>
#include <vector>

#include "AnalyticalFunctionsEnum.h"
#include "SchemasEnum.h"

/**
 * @brief ConfigurationParameter provides bunch of methods used to reinterprate string to other types.
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
	 * Casts value to double.
	 * @return Value as a double.
	 * @throws std::runtime_error if conversion cannot be performed using std::stringstream.
	 */
	double toDouble();

	/**
	 * Casts value to unsigned int.
	 * @return Value as an unsigned int.
	 * @throws std::runtime_error if conversion cannot be performed using std::stringstream.
	 */
	unsigned int toUnsignedInt();

	/**
	 * Casts value to std::vector of doubles.
	 * Each of a values is separated by ',' character.
	 * @return Value as an std::vector of doubles.
	 * @throws std::runtime_error if conversion cannot be performed using std::stringstream.
	 */
	std::vector<double> toVectorOfDouble();

	/**
	 * Casts value to AnalyticalFunctionEnum.
	 * @see AnalyticalFunctionEnum
	 * Correct values are: "exp" for EXP_FUNCTION and "sign" for SIGN_FUNCTION.
	 * @return Value as an AnalyticalFunctionEnum.
	 * @throws std::runtime_error if value to convert is not in a set of correct values.
	 */
	AnalyticalFunctionEnum toAnalyticalFunction();

	/**
	 * Casts value to SchemasEnum.
	 * @see SchemasEnum
	 * Correct values are: "upwind_implicit" for UPWIND_IMPLICIT,
	 *                     "upwind_explicit" for UPWIND_EXPLICIT,
	 *                     "lax-wendroff" for LAX_WENDROFF and
	 *					   "richtmyer-ms" for RICHTMYER_MULTI_STEP.
	 * @return Value as an SchemasEnum.
	 * @throws std::runtime_error if value to convert is not in a set of correct values.
	 */
	SchemasEnum toSchema();

	/**
	 * Casts value to bool.
	 * Correct values are: "true" and "1" for true and "false and "0" for false.
	 * @return Value casted to bool.
	 * @throws std::runtime_error if value to convert is not in a set of correct values.
	 */
	bool toBool();
};

#endif
