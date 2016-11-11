#include "ConfigurationParameterTests.h"
#include "ConfigurationParameter.h"
#include "SchemasEnum.h"

TEST_F(ConfigurationParameterTests, ShouldReturnInt)
{
	ConfigurationParameter p;
	p.value = "123";

	int k = p;
	ASSERT_EQ(123, k);
}

TEST_F(ConfigurationParameterTests, ShouldReturnVector)
{
	ConfigurationParameter p;
	p.value = "10,12,14";

	std::vector<double> k = p;
	ASSERT_EQ(10, k[0]);
	ASSERT_EQ(12, k[1]);
	ASSERT_EQ(14, k[2]);
}

TEST_F(ConfigurationParameterTests, ShouldReturnVector2)
{
	ConfigurationParameter p;
	p.value = "10,12,14,";

	std::vector<double> k = p;
	ASSERT_EQ(10, k[0]);
	ASSERT_EQ(12, k[1]);
	ASSERT_EQ(14, k[2]);
}

TEST_F(ConfigurationParameterTests, ShouldReturnDouble)
{
	ConfigurationParameter p;
	p.value = "123";

	double k = p;
	ASSERT_EQ(123.0, k);
}

TEST_F(ConfigurationParameterTests, ShouldReturnAnalyticalFunctionExpEnum)
{
	ConfigurationParameter p;
	p.value = "exp";

	AnalyticalFunctionEnum k = p;
	ASSERT_EQ(AnalyticalFunctionEnum::EXP_FUNCTION, k);
}

TEST_F(ConfigurationParameterTests, ShouldReturnAnalyticalFunctionESignEnum)
{
	ConfigurationParameter p;
	p.value = "sign";

	AnalyticalFunctionEnum k = p;
	ASSERT_EQ(AnalyticalFunctionEnum::SIGN_FUNCTION, k);
}


TEST_F(ConfigurationParameterTests, ShouldReturnSchemasUpwindImplicitEnum)
{
	ConfigurationParameter p;
	p.value = "upwind_implicit";

	SchemasEnum k = p;
	ASSERT_EQ(SchemasEnum::UPWIND_IMPLICIT, k);
}

TEST_F(ConfigurationParameterTests, ShouldReturnSchemasUpwindExplicitEnum)
{
	ConfigurationParameter p;
	p.value = "upwind_explicit";

	SchemasEnum k = p;
	ASSERT_EQ(SchemasEnum::UPWIND_EXPLICIT, k);
}

TEST_F(ConfigurationParameterTests, ShouldReturnSchemasUpwindLaxWendroffEnum)
{
	ConfigurationParameter p;
	p.value = "lax-wendroff";

	SchemasEnum k = p;
	ASSERT_EQ(SchemasEnum::LAX_WENDROFF, k);
}

TEST_F(ConfigurationParameterTests, ShouldReturnSchemasRichtmyerMultiStepEnum)
{
	ConfigurationParameter p;
	p.value = "richtmyer-ms";

	SchemasEnum k = p;
	ASSERT_EQ(SchemasEnum::RICHTMYER_MULTI_STEP, k);
}