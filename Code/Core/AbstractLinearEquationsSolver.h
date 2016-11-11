#ifndef __H_ABSTRACT_LINEAR_EQUATIONS_SOLVER
#define __H_ABSTRACT_LINEAR_EQUATIONS_SOLVER

#include "AbstractLinearEquationSet.h"
#include "AbstractLinearEquationsResult.h"

class AbstractLinearEquationsSolver
{
public:
	virtual AbstractLinearEquationsResult * solve(AbstractLinearEquationSet * linearEquations) = 0;
};

#endif
