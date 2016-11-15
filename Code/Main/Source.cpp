#if _DEBUG
	#include <vld.h>
#endif
#include "ConfigurationLoader.h"
#include "Configuration.h"
#include "Discretizator.h"
#include "DiscretizationResult.h"
#include "Exception.h"
#include "AbstractDeltaTSearcher.h"
#include "DefaultDeltaTSearcher.h"
#include "ConfigurationLoadingException.h"
#include "DiscretizationParameters.h"
#include "DefaultAnalyticalFunctionsResolver.h"
#include "AbstractAnalyticalFunctionsResolver.h"
#include "AbstractSchemasResolver.h"
#include "DefaultSchemasResolver.h"
#include "WavePointsSummary.h"

#include <iostream>
#include <fstream>

#define PARAMETER_COUNT 5

#define CONFIGURATION_FILE_INDEX 1
#define WAVE_FILE_INDEX 2
#define NORM_FILE_INDEX 3
#define OPTIMAL_DELTA_T_FILE_INDEX 4

int main(int argc, char * argv[])
{
	try
	{
		if (argc != PARAMETER_COUNT)
		{
			std::cout << "Invalid amount of parameters." << std::endl;
		//	return -1;
		}

#if _DEBUG
		char * configurationFile = "C:\\Users\\mrnim\\Desktop\\Repos\\numerical-methods-assignment\\Code\\Configurations\\implicit-upwind-400-sign.conf";
		char * wavesFile = "1";
		char * normsFile = "2";
		char * optimalDeltaTFile = "3";
#else
		char * configurationFile = argv[CONFIGURATION_FILE_INDEX];
		char * wavesFile = argv[WAVE_FILE_INDEX];
		char * normsFile = argv[NORM_FILE_INDEX];
		char * optimalDeltaTFile = argv[OPTIMAL_DELTA_T_FILE_INDEX];
#endif
				
		ConfigurationLoader configurationLoader;
		Configuration * configuration = configurationLoader.loadFromFile(configurationFile);

		AbstractSchemasResolver * schemaResolver = new DefaultSchemasResolver();
		AbstractAnalyticalFunctionsResolver * functionResolver = new DefaultAnalyticalFunctionsResolver();
		
		if (configuration->searchOptimalDeltaT)
		{
			DefaultDeltaTSearcher deltaSearcher(new Configuration(*configuration), new DefaultAnalyticalFunctionsResolver(), new DefaultSchemasResolver());
			configuration->deltaT = deltaSearcher.find();
		}

		double deltaX = (configuration->upperBound - configuration->lowerBound) / configuration->meshSize;

		Discretizator discretizator(
			new DiscretizationParameters(
				configuration->lowerBound,
				configuration->upperBound,
				configuration->acceleration,
				functionResolver->resolve(configuration->analyticalFunction),
				schemaResolver->resolve(configuration->schema, configuration->acceleration, deltaX, configuration->deltaT),
				configuration->meshSize,
				configuration->timeLevels,
				configuration->deltaT
			)
		);

		DiscretizationResult * result = discretizator.discretize();
		
		std::fstream ws;
		ws.open(wavesFile, std::fstream::out | std::fstream::trunc);
		WavesSummary * pointsAtTimeT = result->getValuesAtTimeT();
		ws << *pointsAtTimeT;
		ws.close();

		std::fstream ns;
		ns.open(normsFile, std::fstream::out | std::fstream::trunc);
		NormSummary * norms = result->getNorms();
		std::cout << *norms;
		ns << *norms;
		ns.close();

		std::fstream odts;		
		odts.open(optimalDeltaTFile, std::fstream::out | std::fstream::trunc);
		odts << "Delta T," << configuration->deltaT << std::endl;
		odts << "CFL, " << configuration->acceleration * configuration->deltaT / deltaX << std::endl;;
		std::cout << "Delta T," << configuration->deltaT << std::endl;
		std::cout << "CFL, " << configuration->acceleration * configuration->deltaT / deltaX << std::endl;
		odts.close();

		delete schemaResolver;
		delete functionResolver;
		delete result;
		delete configuration;
		delete norms;

	}
	catch (ConfigurationLoadingException cle)
	{
		std::cout << "ConfigurationLoadingException" << std::endl;
	}
	catch (Exception e)
	{
		std::cout << "Exception" << std::endl;
	}
	catch (std::exception & stde)
	{
		std::cout << stde.what() << std::endl;
	}

	return 0;
}