#include "ResolverTests.h"
#include "AbstractSchemasResolver.h"
#include "AbstractAnalyticalFunctionsResolver.h"

#include "DefaultAnalyticalFunctionsResolver.h"
#include "DefaultSchemasResolver.h"

#include "AnalyticalFunctions.h"
TEST_F(ResolverTests, ShouldReturnSignFunction)
{
	DefaultAnalyticalFunctionsResolver r;

	double (*f)(double, double) = r.resolve(AnalyticalFunctionEnum::EXP_FUNCTION);

	SUCCEED();
}

TEST_F(ResolverTests, ShouldReturnExpFunction)
{
	DefaultAnalyticalFunctionsResolver r;

	double(*f)(double, double) = r.resolve(AnalyticalFunctionEnum::SIGN_FUNCTION);

	SUCCEED();
}

TEST_F(ResolverTests, ShouldReturnUpwindImplicit)
{
	DefaultSchemasResolver r;

	AbstractSchema * s = r.resolve(SchemasEnum::UPWIND_IMPLICIT, 0, 0, 0);

	ASSERT_EQ(typeid(*s), typeid(UpwindImplicitSchema));

	delete s;
}

TEST_F(ResolverTests, ShouldReturnUpwindExplicit)
{
	DefaultSchemasResolver r;

	AbstractSchema * s = r.resolve(SchemasEnum::UPWIND_EXPLICIT, 0, 0, 0);

	ASSERT_EQ(typeid(*s), typeid(UpwindExplicitSchema));

	delete s;
}

TEST_F(ResolverTests, ShouldReturnLaxWendroff)
{
	DefaultSchemasResolver r;

	AbstractSchema * s = r.resolve(SchemasEnum::LAX_WENDROFF, 0, 0, 0);

	ASSERT_EQ(typeid(*s), typeid(LaxWendroffSchema));

	delete s;
}

TEST_F(ResolverTests, ShouldReturnRichtmyerMultiStep)
{
	DefaultSchemasResolver r;

	AbstractSchema * s = r.resolve(SchemasEnum::RICHTMYER_MULTI_STEP, 0, 0, 0);

	ASSERT_EQ(typeid(*s), typeid(RichtmyerMultiStepSchema));

	delete s;
}