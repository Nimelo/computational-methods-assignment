#ifndef __H_EXCEPTION
#define __H_EXCEPTION

#include <stdexcept>

/**
 * Common exception for a project.
 * @author Mateusz Gasior
 */
class Exception : public std::runtime_error
{
public:
	/**
	 * Overriden constructor for explicitly given parameters.
	 * @param val Message of exception.
	 */
	Exception(const char * val) : std::runtime_error(val)
	{

	}
};

#endif
