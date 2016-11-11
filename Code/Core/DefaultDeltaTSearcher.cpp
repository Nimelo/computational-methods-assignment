#include "DefaultDeltaTSearcher.h"
#include "DiscretizationParameters.h"
#include "Discretizator.h"
#include "StabilityConditionException.h"
#include "ZeroPivotException.h"
#include <limits>
#include <iostream>

DefaultDeltaTSearcher::DefaultDeltaTSearcher(Configuration * parameters,
	AbstractAnalyticalFunctionsResolver * functionResolver, AbstractSchemasResolver * schemaResolver)
	: AbstractDeltaTSearcher(parameters, functionResolver, schemaResolver)
{
}

double DefaultDeltaTSearcher::find()
{
	double currentDeltaT = this->configuration->minDeltaT;
	double optimalDeltaT = currentDeltaT;
	double optimalError = DBL_MAX;

	DiscretizationParameters * parameters = new DiscretizationParameters(this->schemasResolver->resolve(this->configuration->schema),
		this->functionResovler->resolve(this->configuration->analyticalFunction),
		this->configuration, currentDeltaT);
	Discretizator * discretizator = new Discretizator(parameters);

	for (currentDeltaT; currentDeltaT < this->configuration->maxDeltaT; currentDeltaT += this->configuration->deltaTStep)
	{
		parameters->deltaT = currentDeltaT;	
		try
		{
			DiscretizationResult * result = discretizator->discretize();
			NormSummary * normSummary = result->getNorms();

			double currentError = 0.0;
			for (unsigned int i = 0; i < normSummary->size(); i++)
			{
				currentError += normSummary->at(i).normTwo;
			}

			if (currentError < optimalError)
			{
				optimalError = currentError;
				optimalDeltaT = currentDeltaT;
			}

			delete normSummary;
			delete result;
		}
		catch (StabilityConditionException & sc)
		{
			std::cout << "StabilityConditionException at dt: " << currentDeltaT << std::endl;
		}	
		catch (ZeroPivotException & pe)
		{
			std::cout << "ZeroPivotException at dt: " << currentDeltaT << std::endl;
		}
		catch (Exception & e)
		{
			std::cout << "Exception at dt: " << currentDeltaT << std::endl << e.what() << std::endl;
		}
	}

	delete discretizator;

	return optimalDeltaT;
}
