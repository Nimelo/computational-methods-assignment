/**
 * @file DefaultSchemasResolver.h
 * @brief Declaration of methods for DefaultSchemasResolver.
 */

#ifndef __H_DEFAULT_SCHEMAS_RESOLVER
#define __H_DEFAULT_SCHEMAS_RESOLVER

#include "AbstractSchemasResolver.h"
#include "SchemasEnum.h"
#include "AbstractSchema.h"

#include "UpwindExplicitSchema.h"
#include "UpwindImplicitSchema.h"
#include "RichtmyerMultiStepSchema.h"
#include "LaxWendroffSchema.h"

/**
 * @brief Default resolver for schemas.
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
	AbstractSchema * resolve(SchemasEnum key, double a, double dx, double dt);
};

#endif
