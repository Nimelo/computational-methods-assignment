/**
 * @file ZeroPivotException.h
 * @brief Declaration of methods for ZeroPivotException.
 */

#ifndef __H_ZERO_PIVOT_EXCEPTION
#define __H_ZERO_PIVOT_EXCEPTION

#include "Exception.h"

/**
 * @brief Exception used when there is a zero in a pivot of the matrix.
 * Used while performing of LU factorization.
 * @see Exception
 * @author Mateusz Gasior
 */
class ZeroPivotException : public Exception
{
};

#endif
