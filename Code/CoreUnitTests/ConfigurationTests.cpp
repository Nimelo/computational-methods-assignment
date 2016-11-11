#include <gtest/gtest.h>
#include <string>
#include <vector>

#include "ConfigurationTests.h"
#include "ConfigurationLoader.h";
#include "Configuration.h"
#include "Discretizator.h"
#include "UpwindImplicitSchema.h"
#include "AnalyticalFunctions.h"

typedef std::vector<std::string> ConfigurationInput;
TEST_F(ConfigurationTests, ShouldLoadConfiguration)
{
	ConfigurationInput lines = {"lowerBound=127",
								"upperBound=123",
								"acceleration=1.0",
								"timeLevels=5,10,23",
								"gridSize=100",
								"schema=upwind_implicit",
								"analyticalFunction=exp",
								"searchOptimalDeltaT=true",
								"deltaT=0.01",
								"minDeltaT=0.0",
								"maxDeltaT=1.0",
								"deltaTStep=23.2"};
	ConfigurationLoader configurationLoader;

	Configuration * configuration = configurationLoader.loadFromLines(lines);

	ASSERT_EQ(127.0, configuration->lowerBound) << "Lower bound: Values are not equal!";
	ASSERT_EQ(123.0, configuration->upperBound) << "Upper bound: Values are not equal!";
	ASSERT_EQ(1.0, configuration->acceleration) << "Acceleration: Values are not equal!";
	ASSERT_EQ(100.0, configuration->meshSize) << "MeshSize: Values are not equal!";
	ASSERT_NO_THROW(configuration->analyticalFunction) << "AnalyticalFunction throwed!";
	ASSERT_EQ(0.01, configuration->deltaT) << "DeltaT: Values are not equal!";

	delete configuration;
}

TEST_F(ConfigurationTests, ShouldPerformUpwindImplicit400)
{
	ConfigurationInput lines = { "lowerBound=-50",
		"upperBound=50",
		"acceleration=1.75",
		"timeLevels=5,10",
		"gridSize=400",
		"schema=upwind_implicit",
		"analyticalFunction=exp",
		"searchOptimalDeltaT=false",
		"deltaT=0.58",
		"minDeltaT=0.01",
		"maxDeltaT=1.0",
		"deltaTStep=0.01" };
	ConfigurationLoader configurationLoader;

	Configuration * configuration = configurationLoader.loadFromLines(lines);
	Discretizator d(
		new DiscretizationParameters(
			1,
			2,
			3,
			AnalyticalFunctions::expFunction,
			new UpwindImplicitSchema(1,0,0),
			123,
			std::vector<double>(),
			0
		)
	);

	delete d.discretize();

	delete configuration;
}
