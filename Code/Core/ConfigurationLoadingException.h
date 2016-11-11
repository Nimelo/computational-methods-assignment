#ifndef __H_CONFIGURATION_LOADING_EXCEPTION
#define __H_CONFIGURATION_LOADING_EXCEPTION

#include "Exception.h"

/**
 * Exception used when there is a problem with loading a confiuration.
 * @see Configuration
 * @see ConfigurationLoader
 * @see Exception
 * @author Mateusz Gasior
 */
class ConfigurationLoadingException : public Exception
{
public:
	/**
	 * Overriden constructor for explicitly given parameters.
	 * @param val Message of exception.
	 */
	ConfigurationLoadingException(const char * msg) : Exception(msg)
	{

	}
};
#endif
