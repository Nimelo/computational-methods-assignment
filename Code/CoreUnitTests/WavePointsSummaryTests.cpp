#include "WavePointsSummaryTests.h"
#include "WavePointsSummary.h"
#include "WavePoints.h"

TEST_F(WavePointsSummaryTests, ErrorInfinity)
{
	WavePointsSummary * s = WavePointsSummaryTests::getTestSummary();
	
	double expected = 10;
	double actual = s->errorNormInfinity();

	ASSERT_EQ(expected, actual);
	delete s;
}

TEST_F(WavePointsSummaryTests, ErrorOne)
{
	WavePointsSummary * s = WavePointsSummaryTests::getTestSummary();

	double expected = 30;
	double actual = s->errorNormOne();

	ASSERT_EQ(expected, actual);
	delete s;
}

TEST_F(WavePointsSummaryTests, ErrorTwo)
{
	WavePointsSummary * s = WavePointsSummaryTests::getTestSummary();

	double expected = sqrt(220);
	double actual = s->errorNormTwo();

	ASSERT_EQ(expected, actual);
	delete s;
}
