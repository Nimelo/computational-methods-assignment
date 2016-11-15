#include "DefaultDeltaTSearcher.h"

#include "AbstractDeltaTSearcher.h"
#include "DiscretizationParameters.h"
#include "Discretizator.h"
#include "StabilityConditionException.h"
#include "Exception.h"

#include <cfloat>
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
	double deltaX = (configuration->upperBound - configuration->lowerBound) / configuration->meshSize;

	DiscretizationParameters * parameters = new DiscretizationParameters(
		this->configuration->lowerBound,
		this->configuration->upperBound,
		this->configuration->acceleration,
		this->functionResovler->resolve(this->configuration->analyticalFunction),
		this->schemasResolver->resolve(this->configuration->schema,
			this->configuration->acceleration,
			deltaX,
			this->configuration->minDeltaT
		),
		this->configuration->meshSize,
		this->configuration->timeLevels,
		this->configuration->minDeltaT
	);

	Discretizator * discretizator = new Discretizator(parameters);

	for (currentDeltaT; currentDeltaT < this->configuration->maxDeltaT; currentDeltaT += this->configuration->deltaTStep)
	{
		delete parameters->schema;
		parameters->schema = this->schemasResolver->resolve(this->configuration->schema,
			this->configuration->acceleration,
			deltaX,
			currentDeltaT
		);

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
		catch (Exception & e)
		{
			std::cout << "Exception at dt: " << currentDeltaT << std::endl;
		}
	}

	delete discretizator;

	return optimalDeltaT;
}