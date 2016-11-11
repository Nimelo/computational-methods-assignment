#ifndef __H_WAVE_POINTS_SUMMARY_TESTS
#define __H_WAVE_POINTS_SUMMARY_TESTS

#include <gtest/gtest.h>

#include "WavePointsSummary.h"
#include "WavePoints.h"

class WavePointsSummaryTests : public ::testing::Test
{	
public:
	static WavePointsSummary * getTestSummary()
	{
		const unsigned int waveSize = 5;
		WavePoints * analytical = new WavePoints(waveSize);
		WavePoints * numerical = new WavePoints(waveSize);

		for (unsigned int i = 0; i < waveSize; i++)
		{
			analytical->at(i) = i;
			numerical->at(i) = 10 - i;
		}

		return new WavePointsSummary(0, numerical, analytical);
	}
};

#endif
