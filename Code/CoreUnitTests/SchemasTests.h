#ifndef __H_SCHEMAS_TESTS
#define __H_SCHEMAS_TESTS

#include <gtest/gtest.h>
#include <vector>
#include <math.h>

class SchemasTests : public ::testing::Test
{
public:
	static std::vector<double> * getSampleWave()
	{
		std::vector<double> * wave = new std::vector<double>(10);
		for (unsigned int  i = 0; i < 10; i++)
		{
			wave->at(i) = (double)i;
		}

		return wave;
	}

	static std::vector<double> * getCorrectWave()
	{
		std::vector<double> * wave = new std::vector<double>(10);

		wave->at(0) = 0;
		wave->at(1) = 1;
		wave->at(2) = 2;
		wave->at(3) = 3;
		wave->at(4) = 4;
		wave->at(5) = 5;
		wave->at(6) = 6;
		wave->at(7) = 7;
		wave->at(8) = 8;
		wave->at(9) = 9;

		return wave;
	}

	static bool compare(std::vector<double> * l, std::vector<double> * r)
	{
		for (unsigned int i = 0; i < l->size(); i++)
		{
			if (l->at(i) != r->at(i)) 
			{
				return false;
			}			
		}

		return true;
	}

	static bool compare(std::vector<double> * l, std::vector<double> * r, double diff)
	{
		for (unsigned int i = 0; i < l->size(); i++)
		{
			if (fabs(l->at(i) - r->at(i)) > diff)
			{
				return false;
			}
		}

		return true;
	}
};

#endif
