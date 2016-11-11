#ifndef __H_STABILITY_CONDITION_EXCEPTION
#define __H_STABILITY_CONDITION_EXCEPTION

#include "Exception.h"

/**
 * Used when schema becomes unstable.
 * @see AbstractSchema
 * @see Exception
 * @author Mateusz Gasior
 */
class StabilityConditionException : public Exception
{
};

#endif
