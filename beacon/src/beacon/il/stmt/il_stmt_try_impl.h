#ifndef BEACON_IL_IL_STM_TRY_H
#define BEACON_IL_IL_STM_TRY_H
#include "../../util/vector.h"
#include "../../util/string_pool.h"
#include "../../env/generic_cache.h"
#include "../il_stmt_interface.h"

struct Enviroment;

typedef struct ILTry {
	Vector* Statements;
	Vector* Catches;
} ILTry;

typedef struct ILCatch {
	GenericCache* GCache;
	StringView Name;
	Vector* Statements;
} ILCatch;

ILStatement* WrapILTry(ILTry* self);

ILTry* NewILTry();

ILCatch* NewILCatch(StringView namev);

void GenerateILTry(ILTry* self, Enviroment* env, CallContext* cctx);

void GenerateILCatch(ILCatch* self, Enviroment* env, CallContext* cctx);

void LoadILTry(ILTry* self, Enviroment* env, CallContext* cctx);

void LoadILCatch(ILCatch* self, Enviroment* env, CallContext* cctx);

void DeleteILCatch(ILCatch* self);

void DeleteILTry(ILTry* self);
#endif
