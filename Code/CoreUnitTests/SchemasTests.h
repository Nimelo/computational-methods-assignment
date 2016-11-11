#ifndef __H_SCHEMAS_TESTS
#define __H_SCHEMAS_TESTS

#include <gtest/gtest.h>
#include "WavePoints.h"
#include <vector>
#include <math.h>

class SchemasTests : public ::testing::Test
{
public:
	static WavePoints * getSampleWave()
	{
		WavePoints * wave = new WavePoints(10);
		for (unsigned int  i = 0; i < 10; i++)
		{
			wave->at(i) = (double)i;
		}

		return wave;
	}

	static WavePoints * getCorrectWave()
	{
		WavePoints * wave = new WavePoints(10);

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

	static bool compare(WavePoints * l, WavePoints * r)
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

	static bool compare(WavePoints * l, WavePoints * r, double diff)
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
