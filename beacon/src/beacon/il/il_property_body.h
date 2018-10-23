#ifndef BEACON_IL_IL_PROPERTY_BODY_H
#define BEACON_IL_IL_PROPERTY_BODY_H
#include "../util/vector.h"
#include "../ast/access_level.h"
#include <stdbool.h>

struct generic_cache;

typedef enum ILPropertyBodyTag {
	IL_PROPERTY_SET_T,
	IL_PROPERTY_GET_T,
} ILPropertyBodyTag;

typedef struct ILPropertyBody {
	AccessLevel Access;
	Vector* Statements;
	ILPropertyBodyTag Tag;
	bool IsShort;
} ILPropertyBody;

#define ILPropertyBody_new(tag) (MallocILPropertyBody(tag, __FILE__, __LINE__))
ILPropertyBody* MallocILPropertyBody(ILPropertyBodyTag tag, const char* filename, int lineno);

void DeleteILPropertyBody(ILPropertyBody* self);
#endif