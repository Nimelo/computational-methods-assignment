#include <vld.h>
#include "Configuration.h"
#include "Discretizator.h"
#include "DiscretizationResult.h"
#include "Exception.h"
#include "ConfigurationLoadingException.h"
#include "DiscretizationParameters.h"
#include "ConfigurationLoader.h"
#include "DefaultAnalyticalFunctionsResolver.h"
#include "AbstractAnalyticalFunctionsResolver.h"
#include "AbstractSchemasResolver.h"
#include "DefaultSchemasResolver.h"
#include "WavePointsSummary.h"
#include "AbstractDeltaTSearcher.h"
#include "DefaultDeltaTSearcher.h"

#include <iostream>
#include <fstream>

#define PARAMETER_COUNT 5

#define CONFIGURATION_FILE_INDEX 1
#define WAVE_FILE_INDEX 2
#define NORM_FILE_INDEX 3
#define OPTIMAL_DELTA_T_FILE_INDEX 4

//MAIN FOR SIMPLE
int main(int argc, char * argv[])
{
	try
	{
		if (argc != PARAMETER_COUNT)
		{
			std::cout << "Invalid amount of parameters." << std::endl;
			exit(-1);
		}

		char * configurationFile = argv[CONFIGURATION_FILE_INDEX];
		char * wavesFile = argv[WAVE_FILE_INDEX];
		char * normsFile = argv[NORM_FILE_INDEX];
		char * optimalDeltaTFile = argv[OPTIMAL_DELTA_T_FILE_INDEX];
		
		ConfigurationLoader configurationLoader;
		Configuration * configuration = configurationLoader.loadFromFile(configurationFile);

		double deltaT = 0.0;
		if (configuration->searchOptimalDeltaT)
		{
			DefaultDeltaTSearcher deltaSearcher(new Configuration(*configuration), new DefaultAnalyticalFunctionsResolver(), new DefaultSchemasResolver());
			deltaT = deltaSearcher.find();
		}
		else
		{
			deltaT = configuration->deltaT;
		}
	
		std::cout << "Delta T is equal to: " << deltaT << std::endl;

		AbstractSchemasResolver * schemaResolver = new DefaultSchemasResolver();
		AbstractAnalyticalFunctionsResolver * functionResolver = new DefaultAnalyticalFunctionsResolver();

		Discretizator discretizator(new DiscretizationParameters(schemaResolver->resolve(configuration->schema),
			functionResolver->resolve(configuration->analyticalFunction),
			configuration,
			deltaT)
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
		ns << *norms;
		ns.close();

		std::fstream odts;		
		odts.open(optimalDeltaTFile, std::fstream::out | std::fstream::trunc);
		odts << deltaT;
		odts.close();

		delete schemaResolver;
		delete functionResolver;
		delete result;
		delete configuration;
		delete norms;

	}
	catch (ConfigurationLoadingException cle)
	{
		std::cout << cle.what() << std::endl;
	}
	catch (Exception e)
	{
		std::cout << e.what() << std::endl;
	}
	catch (std::exception & stde)
	{
		std::cout << stde.what() << std::endl;
	}

	return 0;
}