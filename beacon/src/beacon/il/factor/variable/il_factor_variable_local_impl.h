#ifndef BEACON_IL_IL_FACTOR_VARIABLE_LOCAL_H
#define BEACON_IL_IL_FACTOR_VARIABLE_LOCAL_H
#include "../../../util/vector.h"
#include "../../../util/string_pool.h"
#include "../../il_factor_interface.h"
struct SymbolEntry;
struct Enviroment;
struct GenericType;
struct Field;
struct Property;

typedef enum VariableLocalType {
	VARIABLE_LOCAL_SCOPE_T,
	VARIABLE_LOCAL_FIELD_T,
	VARIABLE_LOCAL_PROPERTY_T,
	VARIABLE_LOCAL_UNDEFINED_T,
} VariableLocalType;

typedef struct FieldWithIndex {
	struct Field* Field;
	int Index;
} FieldWithIndex;

typedef struct PropertyWithIndex {
	struct Property* Property;
	int Index;
} PropertyWithIndex;

/**
 * ローカル変数を表す構造体.
 */
typedef struct ILVariableLocal {
	StringView Name;
	VariableLocalType Type;
	struct GenericType* GType;
	union {
		struct SymbolEntry* Entry;
		FieldWithIndex FieldI;
		PropertyWithIndex PropertyI;
	} Kind;
	Vector* TypeArgs;
} ILVariableLocal;

ILVariableLocal* NewILVariableLocal(StringView namev);

void GenerateILVariableLocal(ILVariableLocal* self, Enviroment* env, CallContext* cctx);

void LoadILVariableLocal(ILVariableLocal * self, Enviroment * env, CallContext* cctx);

struct GenericType* EvalILVariableLocal(ILVariableLocal * self, Enviroment * env, CallContext* cctx);

char* ILVariableLocalToString(ILVariableLocal * self, Enviroment * env);

void DeleteILVariableLocal(ILVariableLocal* self);
#endif