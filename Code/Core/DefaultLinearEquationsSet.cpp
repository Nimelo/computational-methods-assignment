#include "DefaultLinearEquationsSet.h"

DefaultLinearEquationsSet::DefaultLinearEquationsSet(Matrix * matrix, Vector * vector)
	: matrix(matrix), vector(vector)
{
	
}

DefaultLinearEquationsSet::~DefaultLinearEquationsSet()
{
	delete this->matrix;
	delete this->vector;
}

void DefaultLinearEquationsSet::setNewVector(Vector * vector)
{
	if(this->vector != NULL)
		delete this->vector;
	this->vector = vector;
}

unsigned int DefaultLinearEquationsSet::getAmountOfUnknowns()
{
	return (unsigned int)this->vector->getSize();
}

unsigned int DefaultLinearEquationsSet::getWidthOfLinearSet()
{
	return this->matrix->getNcols();
}

unsigned int DefaultLinearEquationsSet::getHeightOfLinearSet()
{
	return this->matrix->getNrows();
}

double DefaultLinearEquationsSet::getRightSideAt(unsigned int index)
{
	return this->vector->at(index);
}

double DefaultLinearEquationsSet::getLinearSetAt(unsigned int column, unsigned int row)
{
	return (*this->matrix)[row][column];
}
