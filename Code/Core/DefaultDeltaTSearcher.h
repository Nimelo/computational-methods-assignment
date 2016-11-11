#ifndef __H_DEFAULT_DELTA_T_SEARCHER
#define __H_DEFAULT_DELTA_T_SEARCHER

#include "AbstractDeltaTSearcher.h"
#include "Configuration.h"

/**
 * Default delta t searcher, which decision making base on norm two.
 * @see AbstractDeltaTSearcher
 * Provides all necessary abstractions for searching for optimal delta t value.
 * @author Mateusz Gasior
 */
class DefaultDeltaTSearcher : public AbstractDeltaTSearcher
{
public:

	/**
	 * Constructor for explicitly given parameters.
	 * @param parameters Configuration.
	 * @param functionResolver Resolver for analytical functions.
	 * @param schemaResolver Resolver for schemas.
	 */
	DefaultDeltaTSearcher(Configuration * parameters,
		AbstractAnalyticalFunctionsResolver * functionResolver, 
		AbstractSchemasResolver * schemaResolver);
	/**
	 * Searches for optimal delta t.
	 * Decision is made by comparing norm two.
	 * @return Optimal delta t based on configuration.
	 */
	virtual double find() override;
};

#endif
