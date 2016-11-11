#ifndef __H_ABSTRACT_LINEAR_EQUATIONS_RESULT
#define __H_ABSTRACT_LINEAR_EQUATIONS_RESULT

class AbstractLinearEquationsResult
{
public:
	virtual ~AbstractLinearEquationsResult()
	{

	}
	virtual unsigned int getSolutionSize() = 0;
	virtual double getSolutionAt(unsigned int index) = 0;
};

#endif
