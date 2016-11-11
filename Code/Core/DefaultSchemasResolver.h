#ifndef __H_DEFAULT_SCHEMAS_RESOLVER
#define __H_DEFAULT_SCHEMAS_RESOLVER

#include "SchemasEnum.h"
#include "AbstractSchema.h"
#include "AbstractSchemasResolver.h"

#include "UpwindExplicitSchema.h"
#include "UpwindImplicitSchema.h"
#include "RichtmyerMultiStepSchema.h"
#include "LaxWendroffSchema.h"

/**
 * Default resolver for schemas.
 * @see AbstractSchemasResolver
 * @author Mateusz Gasior
 */
class DefaultSchemasResolver : public AbstractSchemasResolver
{
public:
	/**
	 * Resolves schema by given key.
	 * @see SchemasEnum
	 * @param key Key for schema.
	 * @return Schema corresponding to the given key.
	 */
	AbstractSchema * resolve(SchemasEnum key)
	{
		switch (key)
		{
		case UPWIND_EXPLICIT:
			return new UpwindExplicitSchema();
		case UPWIND_IMPLICIT:
			return new UpwindImplicitSchema();
		case LAX_WENDROFF:
			return new LaxWendroffSchema();
		case RICHTMYER_MULTI_STEP:
			return new RichtmyerMultiStepSchema();
		}
	}
};

#endif
