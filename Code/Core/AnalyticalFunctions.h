#ifndef __H_ANALYTICAL_FUNCTIONS
#define __H_ANALYTICAL_FUNCTIONS

/**
 * Contains implementations of analytical function that are used in discretization process.
 * @author Mateusz Gasior
 */
class AnalyticalFunctions
{
private:
	/**
	 * Sign function.
	 * @param val Value.
	 * @return Response of sign function.
	 */
	static double sign(double val);
public:
	/**
	 * Function that uses exponential mathematical function.
	 * @param x Space dimension.
	 * @param t Time dimension.
	 * @return Calculated value.
	 */
	static double expFunction(double x, double t);

	/**
	 * Function that uses sign mathematical function.
	 * @param x Space dimension.
	 * @param t Time dimension.
	 * @return Calculated value.
	 */
	static double signFunction(double x, double t);
};

#endif
