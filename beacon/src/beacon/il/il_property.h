//BEGIN-AUTOGENERATED-BLOCK
/**
 * @file il_property.h
 * @brief ここに概要を記述します
 * @author koya
 * @date 2018/10/31
 */
//END-AUTOGENERATED-BLOCK

#ifndef BEACON_IL_IL_PROPERTY_H
#define BEACON_IL_IL_PROPERTY_H
#include "../ast/access_level.h"
#include "../ast/modifier_type.h"
#include "../util/string_pool.h"
#include "il_property_body.h"
struct GenericCache;

typedef struct ILProperty {
	struct GenericCache* GCache;
	bc_AccessLevel Access;
	bc_ModifierType Modifier;
	StringView Name;
	ILPropertyBody* Set;
	ILPropertyBody* Get;
} ILProperty;

#define ILNewProperty(namev) (MallocILProperty(namev, __FILE__, __LINE__))
ILProperty* MallocILProperty(StringView namev, const char* filename, int lineno);

void DeleteILProperty(ILProperty* self);
#endif