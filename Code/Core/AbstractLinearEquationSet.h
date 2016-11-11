#ifndef __H_ABSTRACT_LINEAR_EQUATION_SET
#define __H_ABSTRACT_LINEAR_EQUATION_SET

class AbstractLinearEquationSet
{
public:
	virtual unsigned int getAmountOfUnknowns() = 0;
	virtual unsigned int getWidthOfLinearSet() = 0;
	virtual unsigned int getHeightOfLinearSet() = 0;

	virtual double getRightSideAt(unsigned int index) = 0;
	virtual double getLinearSetAt(unsigned int column, unsigned int row) = 0;
};

#endif
