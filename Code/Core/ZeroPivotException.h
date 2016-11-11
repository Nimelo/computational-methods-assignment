#ifndef __H_ZERO_PIVOT_EXCEPTION
#define __H_ZERO_PIVOT_EXCEPTION

#include "Exception.h"

/**
 * Exception used when there is a zero in a pivot of the matrix.
 * Used while performing of LU factorization.
 * @see Exception
 * @author Mateusz Gasior
 */
class ZeroPivotException : public Exception
{
public:
	/**
	 * Overriden constructor for explicitly given parameters.
	 * @param val Message of exception.
	 */
	ZeroPivotException(const char * msg) : Exception(msg)
	{

	}
};

#endif
