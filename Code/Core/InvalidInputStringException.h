#ifndef __H_INVALID_INPUT_STRING_EXCEPTION
#define __H_INVALID_INPUT_STRING_EXCEPTION

#include <string>
#include "Exception.h"

class InvalidInputStringException : public Exception
{
protected:
	std::string inputString;
public:
	InvalidInputStringException(const char * msg, std::string inputString) : Exception(msg)
	{
		this->inputString = inputString;
	}

	std::string getInputString() const
	{
		return this->inputString;
	}
};

#endif
