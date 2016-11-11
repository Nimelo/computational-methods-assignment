#include <math.h>
#include "DefaultLinearEquationsSolver.h"
#include "ZeroPivotException.h"


Matrix * DefaultLinearEquationsSolver::getMatrixA(AbstractLinearEquationSet * linearEquations)
{
	Matrix * a = new Matrix(linearEquations->getHeightOfLinearSet(), linearEquations->getWidthOfLinearSet());

	for (unsigned int row = 0; row < linearEquations->getHeightOfLinearSet(); row++)
	{
		for (unsigned int column = 0; column < linearEquations->getWidthOfLinearSet(); column++)
		{
			(*a)[row][column] = linearEquations->getLinearSetAt(column, row);
		}
	}

	return a;
}

Vector * DefaultLinearEquationsSolver::getVectorB(AbstractLinearEquationSet * linearEquations)
{
	Vector * b = new Vector(linearEquations->getAmountOfUnknowns());

	for (unsigned int index = 0; index < linearEquations->getAmountOfUnknowns(); index++)
	{
		(*b)[index] = linearEquations->getRightSideAt(index);
	}

	return b;
}

DefaultLinearEquationsSolver::DefaultLinearEquationsSolver(double limit)
	: limit(limit)
{
}

AbstractLinearEquationsResult * DefaultLinearEquationsSolver::solve(AbstractLinearEquationSet * linearEquations)
{
	unsigned int n = linearEquations->getAmountOfUnknowns();
	Matrix * a = this->getMatrixA(linearEquations);
	Vector * b = this->getVectorB(linearEquations);

	// declare l and u
	Matrix l(n, n), u(n, n);

	// declare p
	Matrix p(n, n);

	// reorder
	this->reorder(*a, n, p);

	// multiply p by a
	Matrix m = p*(*a);

	// factorise
	this->factorizationLU(m, l, u, n);

	Vector z = p*(*b);
	// solve
	Vector * x = this->solveLU(l, u, z, n);

	delete a;
	delete b;

	return new DefaultLinearEquationsResult(x);
}

void DefaultLinearEquationsSolver::factorizationLU(const Matrix & a, Matrix & l, Matrix & u, int n)
{
	double mult;

	Matrix temp(a);

	// LU decomposition without pivoting
	for (int k = 0; k < n - 1; k++) {
		for (int i = k + 1; i < n; i++) {
			if (fabs(temp[k][k]) < limit) throw ZeroPivotException();
			mult = temp[i][k] / temp[k][k];
			temp[i][k] = mult;                      // entries of L are saved in temp
			for (int j = k + 1; j < n; j++) {
				temp[i][j] -= mult*temp[k][j];      // entries of U are saved in temp
				if (fabs(temp[i][i]) < limit) throw ZeroPivotException();
			}
		}
	}

	// create l and u from temp
	for (int i = 0; i<n; i++) l[i][i] = 1.0;
	for (int i = 1; i<n; i++)
		for (int j = 0; j<i; j++) l[i][j] = temp[i][j];

	for (int i = 0; i<n; i++)
		for (int j = i; j<n; j++) u[i][j] = temp[i][j];
}

Vector * DefaultLinearEquationsSolver::solveLU(const Matrix & l, const Matrix & u, const Vector & b, int n)
{
	Vector * temp = new Vector(b);

	// forward substitution for L y = b.
	for (int i = 1; i < n; i++)
		for (int j = 0; j < i; j++)
			(*temp)[i] -= l[i][j] * (*temp)[j];


	// back substitution for U x = y.  
	for (int i = n - 1; i >= 0; i--) {
		for (int j = i + 1; j < n; j++) (*temp)[i] -= u[i][j] * (*temp)[j];
		(*temp)[i] /= u[i][i];
	}

	return temp;
}

void DefaultLinearEquationsSolver::reorder(const Matrix & a, int n, Matrix & p)
{
	// Note: pivoting information is stored in temperary vector pvt
	int pvtk, pvti;
	double aet, tmp, mult;

	std::vector<int> pvt(n);
	Matrix temp(a);

	for (int k = 0; k < n; k++) pvt[k] = k;

	Vector scale(n);             // find scale vector
	for (int k = 0; k < n; k++) {
		scale[k] = 0;
		for (int j = 0; j < n; j++)
			if (fabs(scale[k]) < fabs(temp[k][j])) scale[k] = fabs(temp[k][j]);
	}

	for (int k = 0; k < n - 1; k++) {            // main elimination loop

												 // find the pivot in column k in rows pvt[k], pvt[k+1], ..., pvt[n-1]
		int pc = k;
		aet = fabs(temp[pvt[k]][k] / scale[k]);
		for (int i = k + 1; i < n; i++) {
			tmp = fabs(temp[pvt[i]][k] / scale[pvt[i]]);
			if (tmp > aet) {
				aet = tmp;
				pc = i;
			}
		}
		if (fabs(aet) < limit) throw ZeroPivotException();
		if (pc != k) {                      // swap pvt[k] and pvt[pc]
			int ii = pvt[k];
			pvt[k] = pvt[pc];
			pvt[pc] = ii;
		}

		// now eliminate the column entries logically below mx[pvt[k]][k]
		pvtk = pvt[k];                           // pivot row
		for (int i = k + 1; i < n; i++) {
			pvti = pvt[i];
			if (temp[pvti][k] != 0) {
				mult = temp[pvti][k] / temp[pvtk][k];
				temp[pvti][k] = mult;
				for (int j = k + 1; j < n; j++) temp[pvti][j] -= mult*temp[pvtk][j];
			}
		}
	}
	for (int i = 0; i<n; i++) p[i][pvt[i]] = 1.0;
}
