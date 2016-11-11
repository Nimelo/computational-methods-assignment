#ifndef __H_DEFAULT_LINEAR_EQUATIONS_RESULT
#define __H_DEFAULT_LINEAR_EQUATIONS_RESULT

#include "AbstractLinearEquationsResult.h"
#include "vector.h"

class DefaultLinearEquationsResult : public AbstractLinearEquationsResult
{
private:
	Vector * solution;
public:
	DefaultLinearEquationsResult(Vector * solution);
	~DefaultLinearEquationsResult();
	virtual unsigned int getSolutionSize();
	virtual double getSolutionAt(unsigned int index);

};

#endif
