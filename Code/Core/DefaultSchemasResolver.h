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
	 * @param a Acceleration.
	 * @param dx Delta X.
	 * @param dt Delta T.
	 * @return Schema corresponding to the given key.
	 */
    AbstractSchema * resolve(SchemasEnum key, double a, double dx, double dt)
	{
		switch (key)
		{
		case UPWIND_EXPLICIT:
			return new UpwindExplicitSchema(a, dx, dt);
		case UPWIND_IMPLICIT:
			return new UpwindImplicitSchema(a, dx, dt);
		case LAX_WENDROFF:
			return new LaxWendroffSchema(a, dx, dt);
		case RICHTMYER_MULTI_STEP:
			return new RichtmyerMultiStepSchema(a, dx, dt);
		}
	}
};

#endif
