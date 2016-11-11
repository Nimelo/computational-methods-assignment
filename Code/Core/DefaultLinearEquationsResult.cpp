#include "DefaultLinearEquationsResult.h"

DefaultLinearEquationsResult::DefaultLinearEquationsResult(Vector * solution)
	: solution(solution)
{
}

DefaultLinearEquationsResult::~DefaultLinearEquationsResult()
{
	delete this->solution;
}

unsigned int DefaultLinearEquationsResult::getSolutionSize()
{
	return this->solution->getSize();
}

double DefaultLinearEquationsResult::getSolutionAt(unsigned int index)
{
	return (*this->solution)[index];
}
