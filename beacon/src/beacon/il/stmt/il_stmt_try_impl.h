#ifndef BEACON_IL_IL_STM_TRY_H
#define BEACON_IL_IL_STM_TRY_H
#include "../../util/vector.h"
#include "../../util/string_pool.h"
#include "../../env/generic_cache.h"
#include "../il_stmt_interface.h"

struct enviroment;

typedef struct il_stmt_try {
	vector* statement_list;
	vector* catch_list;
} il_stmt_try;

typedef struct il_stmt_catch {
	generic_cache* fqcn;
	string_view namev;
	vector* statement_list;
} il_stmt_catch;

il_stmt* il_stmt_wrap_try(il_stmt_try* self);

il_stmt_try* il_stmt_try_new();

il_stmt_catch* il_stmt_catch_new(string_view namev);

void il_stmt_try_dump(il_stmt_try* self, int depth);

void il_stmt_catch_dump(il_stmt_catch* self, int depth);

void il_stmt_try_generate(il_stmt_try* self, struct enviroment* env, call_context* cctx);

void il_stmt_catch_generate(il_stmt_catch* self, struct enviroment* env, call_context* cctx);

void il_stmt_try_load(il_stmt_try* self, struct enviroment* env, call_context* cctx);

void il_stmt_catch_load(il_stmt_catch* self, struct enviroment* env, call_context* cctx);

void il_stmt_catch_delete(il_stmt_catch* self);

void il_stmt_try_delete(il_stmt_try* self);
#endif
