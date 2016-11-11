#ifndef __H_UPWIND_IMPLICIT_SCHEMA
#define __H_UPWIND_IMPLICIT_SCHEMA

#include <vector>

#include "AbstractSchema.h"
#include "StabilityConditionException.h"
#include "DefaultLinearEquationsSet.h"
#include "DefaultLinearEquationsSolver.h"
#include "ZeroPivotException.h"
#include "AbstractLinearEquationsResult.h"
#include "vector.h"
#include "matrix.h"

/**
 * Implementaion of upwind implicit method.
 * @see AbstractSchema
 * Provides all methods that have to be used by discretizator.
 * Stores calculated matrices for increasing performance.
 * @author Mateusz Gasior
 */
class UpwindImplicitSchema : public AbstractSchema
{
private:
	/**
	 * Factorized matrix L.
	 */
	Matrix * l;

	/**
	 * Factorized matrix U.
	 */
	Matrix * u;

	/**
	 * Matrix given by reordering matrix A.
	 */
	Matrix * p;

	/**
	 * Value of last coefficient.
	 */
	double lastCoefficient;

	/**
	 * Flag that indicates if matrices are initialized.
	 */
	bool isInit = false;

	/**
	 * Returns vector of points based on wave.
	 * Vector does not contain end values.
	 * @param wave Wave.
	 * @return Vector of points based on wave.
	 */
	Vector * getVector(std::vector<double> * wave)
	{
		Vector * b = new Vector(wave->size() - 2);

		for (unsigned int i = 1; i < wave->size() - 1; i++)
		{
			(*b)[i - 1] = (*wave)[i];
		}

		return b;
	}
	
	/**
	 * Creates matrix based on input parameters for solving linear equation used in upwind implicit schema. 
	 * @param size Size of the return matrix.
	 * @return Matrix based on input parameters, used for calculation of next time step of the wave.
	 */
	Matrix * getMatrix(unsigned int size)
	{
		double c = (this->accelertaion * this->deltaT) / this->deltaX;
		double halfC = 0.5 * c;
		Matrix * matrix = new Matrix(size, size);

		unsigned int index = 0;

		(*matrix)[0][0] = 1.0;
		(*matrix)[0][1] = halfC;
		for (unsigned int row = 1; row < size - 1; row++)
		{
			(*matrix)[row][index] = -halfC;
			(*matrix)[row][index + 1] = 1.0;
			(*matrix)[row][index + 2] = halfC;
			++index;
		}
		(*matrix)[size - 1][size - 2] = -halfC;
		(*matrix)[size - 1][size - 1] = 1.0;

		return matrix;
	}

	/**
	 * Deletes matrices.
	 */
	void deleteMatricies()
	{
		if (this->l != nullptr)
			delete this->l;
		if (this->u != nullptr)
			delete this->u;
		if (this->p != nullptr)
			delete this->p;
	}
public:

	/**
	* Checks the stability condition for given parameters.
	* @throw StabilityConditionException if calculated coefficient (CFL) is negative.
	*/
	void checkStabilityCondition()
	{
		double coefficient = (this->accelertaion * this->deltaT) / this->deltaX;

		if (coefficient <= 0)
			throw StabilityConditionException("Schema is unstable.");
	}

	/**
	* Applies schema for wave and given parameters.
	* @param previousWave previousWave that is base for next time step discretization.
	* @param dx Delta x.
	* @param dt Delta t.
	* @param a Acceleration.
	* @return Wave for next time step.
	*/
	std::vector<double> * apply(std::vector<double> * previousWave)
	{
		DefaultLinearEquationsSolver solver(1.e-20);
		double currentCoefficient = (this->accelertaion * this->deltaT) / this->deltaX;

		if (!isInit || currentCoefficient != lastCoefficient)
		{
			Matrix * matrixA = this->getMatrix(previousWave->size() - 2);

			if (!isInit)
			{
				this->p = new Matrix(matrixA->getNrows(), matrixA->getNcols());
				this->l = new Matrix(matrixA->getNrows(), matrixA->getNcols());
				this->u = new Matrix(matrixA->getNrows(), matrixA->getNcols());
				isInit = true;
			}
			try {
				solver.reorder(*matrixA, matrixA->getNcols(), *p);
				solver.factorizationLU((*p)*(*matrixA), (*this->l), (*this->u), matrixA->getNcols());
				delete matrixA;
			}
			catch (ZeroPivotException & zpe)
			{
				delete matrixA;
				throw zpe;
			}			
		}	

		this->lastCoefficient = currentCoefficient;
		Vector * b = this->getVector(previousWave);
		Vector newB(*p**b);
		Vector * result = solver.solveLU(*this->l, *this->u, newB, this->u->getNcols());

		std::vector<double> * newWave = new std::vector<double>(previousWave->size());

		newWave->at(0) = previousWave->at(0);
		for (unsigned int i = 0; i < (unsigned int)result->getSize(); i++)
		{
			newWave->at(i + 1) = result->at(i);
		}
		newWave->at(previousWave->size() - 1) = previousWave->at(previousWave->size() - 1);

		delete b;
		delete result;
		return newWave;
	}

	/**
	* Explicitly defined constructor.
	* @param a Acceleration.
	* @param dx Delta x.
	* @param dt Delta t.
	*/
	UpwindImplicitSchema(double a, double dx, double dt)
		: AbstractSchema(a, dx, dt)
	{
		this->l = nullptr;
		this->u = nullptr;
		this->p = nullptr;
	}

	/**
	 * Default destructor.
	 */
	~UpwindImplicitSchema()
	{
		this->deleteMatricies();
	}

};

#endif
