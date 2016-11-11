#ifndef __H_ABSTRACT_SCHEMAS_RESOLVER
#define __H_ABSTRACT_SCHEMAS_RESOLVER

#include "SchemasEnum.h"
#include "AbstractSchema.h"

/**
 * Abstraction for resolving schema for discretization.
 * @author Mateusz Gasior
 */
class AbstractSchemasResolver
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
	virtual AbstractSchema * resolve(SchemasEnum key, double a, double dx, double dt) = 0;
};

#endif
