#include "LinearEquationsSolvingRoutineTests.h"

#include "DefaultLinearEquationsSolver.h"
#include "DefaultLinearEquationsResult.h"
#include "DefaultLinearEquationsSet.h"
#include "matrix.h"
#include "vector.h"

TEST_F(LinearEquationsSolvingRoutineTests, ShouldSolveTheProblemCorrectly)
{
	Matrix * a = LinearEquationsSolvingRoutineTests::getTestMatrix1();
	Vector * b = LinearEquationsSolvingRoutineTests::getTestVector1();
	Vector * x = LinearEquationsSolvingRoutineTests::getXVector1();

	DefaultLinearEquationsSet * linearEquations = new DefaultLinearEquationsSet(a, b);
	DefaultLinearEquationsSolver solver(1.e-20);

	AbstractLinearEquationsResult * result = solver.solve(linearEquations);

	for (unsigned int i = 0; i < result->getSolutionSize(); i++)
	{
		ASSERT_EQ((*x)[i], result->getSolutionAt(i));
	}

	delete linearEquations;
	delete x;
	delete result;
}

TEST_F(LinearEquationsSolvingRoutineTests, ShouldSolveTheProblemCorrectly2)
{
	Matrix * a = LinearEquationsSolvingRoutineTests::getTestMatrix1();
	Vector * b = LinearEquationsSolvingRoutineTests::getTestVector1();
	Vector * correctX = LinearEquationsSolvingRoutineTests::getXVector1();

	DefaultLinearEquationsSet * linearEquations = new DefaultLinearEquationsSet(a, b);
	DefaultLinearEquationsSolver solver(1.e-20);

	unsigned int n = b->getSize();

	// declare l and u
	Matrix l(n, n), u(n, n);

	// declare p
	Matrix p(n, n);

	// reorder
	solver.reorder(*a, n, p);

	// multiply p by a
	Matrix m = p*(*a);

	// factorise
	solver.factorizationLU(m, l, u, n);

	// solve
	Vector * x = solver.solveLU(l, u, p*(*b), n);
	for (unsigned int i = 0; i < correctX->getSize(); i++)
	{
		ASSERT_EQ((*correctX)[i], (*x)[i]);
	}
	delete linearEquations;
	delete x;
	delete correctX;
}

TEST_F(LinearEquationsSolvingRoutineTests, FactorizationLUSHouldReturnCorrectValues)
{
	Matrix * a = LinearEquationsSolvingRoutineTests::getTestMatrix1();
	Vector * b = LinearEquationsSolvingRoutineTests::getTestVector1();
	
	Matrix * correctL = LinearEquationsSolvingRoutineTests::getLMatrix1();
	Matrix * correctU = LinearEquationsSolvingRoutineTests::getUMatrix1();

	Matrix p(a->getNrows(), a->getNcols());
	Matrix l(a->getNrows(), a->getNcols());
	Matrix u(a->getNrows(), a->getNcols());

	DefaultLinearEquationsSet * linearEquations = new DefaultLinearEquationsSet(a, b);
	DefaultLinearEquationsSolver solver(1.e-20);

	solver.reorder(*a, a->getNcols(), p);

	Matrix m = p*(*a);
	solver.factorizationLU(m, l, u, a->getNcols());

	ASSERT_EQ(true, (*correctL) == l);
	ASSERT_EQ(true, (*correctU) == u);

	delete linearEquations;
	delete correctL;
	delete correctU;
}

TEST_F(LinearEquationsSolvingRoutineTests, ReorderShouldReturnCorrectP)
{
	Matrix * a = LinearEquationsSolvingRoutineTests::getTestMatrix1();
	Vector * b = LinearEquationsSolvingRoutineTests::getTestVector1();

	Matrix * correctP = LinearEquationsSolvingRoutineTests::getPMatrix1();

	Matrix p(a->getNrows(), a->getNcols());

	DefaultLinearEquationsSolver solver(1.e-20);

	solver.reorder(*a, a->getNcols(), p);

	ASSERT_EQ(true, (*correctP) == p);

	delete correctP;
	delete a;
	delete b;
}