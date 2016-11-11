#ifndef __H_SCHEMAS_ENUM
#define __H_SCHEMAS_ENUM

/**
 * Enumeration for schemas used in disretization process.
 * Stores information about schema that should be applied.
 * @author Mateusz Gasior
 */
enum SchemasEnum
{
	UPWIND_EXPLICIT,
	UPWIND_IMPLICIT,
	LAX_WENDROFF,
	RICHTMYER_MULTI_STEP
};

#endif
