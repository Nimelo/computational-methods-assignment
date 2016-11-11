#ifndef __H_LINEAR_EQUATIONS_SOLVING_ROUTINE_TESTS
#define __H_LINEAR_EQUATIONS_SOLVING_ROUTINE_TESTS

#include <gtest/gtest.h>

#include "matrix.h"
#include "vector.h"

class LinearEquationsSolvingRoutineTests : public ::testing::Test
{
public:
	static Matrix * getTestMatrix1()
	{
		unsigned int unknowns = 4;
		Matrix * a = new Matrix(unknowns, unknowns);

		(*a)[0][0] = 1;
		(*a)[0][1] = 4;
		(*a)[0][2] = 2;
		(*a)[0][3] = 3;

		(*a)[1][0] = 1;
		(*a)[1][1] = 2;
		(*a)[1][2] = 1;
		(*a)[1][3] = 0;

		(*a)[2][0] = 2;
		(*a)[2][1] = 6;
		(*a)[2][2] = 3;
		(*a)[2][3] = 1;

		(*a)[3][0] = 0;
		(*a)[3][1] = 0;
		(*a)[3][2] = 1;
		(*a)[3][3] = 4;

		return a;
	}

	static Vector * getTestVector1()
	{
		unsigned int unknowns = 4;

		Vector * b = new Vector(unknowns);

		(*b)[0] = 1;
		(*b)[1] = 2;
		(*b)[2] = 3;
		(*b)[3] = 4;

		return b;
	}

	static Vector * getXVector1()
	{
		unsigned int unknowns = 4;

		Vector * b = new Vector(unknowns);

		(*b)[0] = 3;
		(*b)[1] = -2.5;
		(*b)[2] = 4;
		(*b)[3] = 0;

		return b;
	}

	static Matrix * getLMatrix1()
	{
		unsigned int unknowns = 4;
		Matrix * a = new Matrix(unknowns, unknowns);

		(*a)[0][0] = 1;
		(*a)[0][1] = 0;
		(*a)[0][2] = 0;
		(*a)[0][3] = 0;

		(*a)[1][0] = 1;
		(*a)[1][1] = 1;
		(*a)[1][2] = 0;
		(*a)[1][3] = 0;

		(*a)[2][0] = 0;
		(*a)[2][1] = 0;
		(*a)[2][2] = 1;
		(*a)[2][3] = 0;

		(*a)[3][0] = 2;
		(*a)[3][1] = 1;
		(*a)[3][2] = 0;
		(*a)[3][3] = 1;

		return a;
	}

	static Matrix * getUMatrix1()
	{
		unsigned int unknowns = 4;
		Matrix * a = new Matrix(unknowns, unknowns);

		(*a)[0][0] = 1;
		(*a)[0][1] = 2;
		(*a)[0][2] = 1;
		(*a)[0][3] = 0;

		(*a)[1][0] = 0;
		(*a)[1][1] = 2;
		(*a)[1][2] = 1;
		(*a)[1][3] = 3;

		(*a)[2][0] = 0;
		(*a)[2][1] = 0;
		(*a)[2][2] = 1;
		(*a)[2][3] = 4;

		(*a)[3][0] = 0;
		(*a)[3][1] = 0;
		(*a)[3][2] = 0;
		(*a)[3][3] = -2;

		return a;
	}

	static Matrix * getPMatrix1()
	{
		unsigned int unknowns = 4;
		Matrix * a = new Matrix(unknowns, unknowns);

		(*a)[0][0] = 0;
		(*a)[0][1] = 1;
		(*a)[0][2] = 0;
		(*a)[0][3] = 0;

		(*a)[1][0] = 1;
		(*a)[1][1] = 0;
		(*a)[1][2] = 0;
		(*a)[1][3] = 0;

		(*a)[2][0] = 0;
		(*a)[2][1] = 0;
		(*a)[2][2] = 0;
		(*a)[2][3] = 1;

		(*a)[3][0] = 0;
		(*a)[3][1] = 0;
		(*a)[3][2] = 1;
		(*a)[3][3] = 0;

		return a;
	}
};

#endif
