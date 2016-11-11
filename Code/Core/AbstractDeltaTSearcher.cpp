#include "AbstractDeltaTSearcher.h"

AbstractDeltaTSearcher::AbstractDeltaTSearcher(Configuration * parameters,
	AbstractAnalyticalFunctionsResolver * functionResolver, AbstractSchemasResolver * schemaResolver)
	: configuration(parameters), functionResovler(functionResolver), schemasResolver(schemaResolver)
{
}

AbstractDeltaTSearcher::~AbstractDeltaTSearcher()
{
	delete this->configuration;
	delete this->functionResovler;
	delete this->schemasResolver;
}
