#ifndef __H_EXCEPTION
#define __H_EXCEPTION

#include <exception>

/**
 * Common exception for a project.
 * @author Mateusz Gasior
 */
class Exception : public std::exception
{
public:
	/**
	 * Overriden constructor for explicitly given parameters.
	 * @param val Message of exception.
	 */
	Exception(const char * val) : std::exception(val)
	{

	}
};

#endif
