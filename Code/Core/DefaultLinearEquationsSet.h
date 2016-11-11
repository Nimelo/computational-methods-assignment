#ifndef __H_DEFAULT_LINEAR_EQUATIONS_SET
#define __H_DEFAULT_LINEAR_EQUATIONS_SET

#include "AbstractLinearEquationSet.h"
#include "matrix.h"
#include "vector.h"

class DefaultLinearEquationsSet : public AbstractLinearEquationSet
{
private:
	Matrix * matrix;
	Vector * vector;
public:

	DefaultLinearEquationsSet(Matrix * matrix, Vector * vector);
	~DefaultLinearEquationsSet();

	void setNewVector(Vector * vector);

	// Inherited via AbstractLinearEquationSet
	virtual unsigned int getAmountOfUnknowns();

	virtual unsigned int getWidthOfLinearSet();

	virtual unsigned int getHeightOfLinearSet();

	virtual double getRightSideAt(unsigned int index);

	virtual double getLinearSetAt(unsigned int column, unsigned int row);

};


#endif
