#ifndef __H_DEFAULT_LINEAR_EQUATIONS_SOLVER
#define __H_DEFAULT_LINEAR_EQUATIONS_SOLVER

#include "AbstractLinearEquationsSolver.h"
#include "DefaultLinearEquationsResult.h"
#include "matrix.h"
#include "vector.h"

class DefaultLinearEquationsSolver : public AbstractLinearEquationsSolver
{
private:
	Matrix * getMatrixA(AbstractLinearEquationSet * linearEquations);
	Vector * getVectorB(AbstractLinearEquationSet * linearEquations);
	double limit;
protected:
	
public:
	DefaultLinearEquationsSolver(double limit);

	virtual AbstractLinearEquationsResult * solve(AbstractLinearEquationSet * linearEquations);
	void factorizationLU(const Matrix & a, Matrix & l, Matrix & u, int n);
	Vector * solveLU(const Matrix & l, const Matrix & u, const Vector & b, int n);
	void reorder(const Matrix & a, int n, Matrix & p);
};


#endif
