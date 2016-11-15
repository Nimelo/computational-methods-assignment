#ifndef __H_ABSTRACT_DELTA_T_SEARCHER
#define __H_ABSTRACT_DELTA_T_SEARCHER

#include "Configuration.h"
#include "AbstractAnalyticalFunctionsResolver.h"
#include "AbstractSchemasResolver.h"

/**
* Abstraction for searching for optimal delta t value.
* Provides all necessary abstractions for searching for optimal delta t value.
* @author Mateusz Gasior
*/
class AbstractDeltaTSearcher
{
protected:

	/**
	* Configuration for discretization process.
	* @see Configuration
	*/
	Configuration * configuration;

	/**
	* Function resolver.
	* @see AbstractAnalyticalFunctionsResolver
	*/
	AbstractAnalyticalFunctionsResolver * functionResovler;

	/**
	* Schemas resolver.
	* @see AbstractSchemasResolver
	*/
	AbstractSchemasResolver * schemasResolver;
public:

	/**
	* Constructor for explicitly given parameters.
	* @param parameters Configuration.
	* @param functionResolver Resolver for analytical functions.
	* @param schemaResolver Resolver for schemas.
	*/
	explicit AbstractDeltaTSearcher(Configuration * parameters, AbstractAnalyticalFunctionsResolver * functionResolver, AbstractSchemasResolver * schemaResolver);

	/**
	* Default destructor.
	*/
	virtual ~AbstractDeltaTSearcher();

	/**
	* Searches for optimal delta t.
	* @return Optimal delta t based on configuration.
	*/
	virtual double find() = 0;
};

#endif