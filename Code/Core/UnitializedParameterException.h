#ifndef __H_UNINITIALIZED_PARAMETER_EXCEPTION
#define __H_UNINITIALIZED_PARAMETER_EXCEPTION

#include "Exception.h"

class UnitializedParameterException : public Exception
{
public:
	UnitializedParameterException() : Exception("")
	{

	}
};
#endif
