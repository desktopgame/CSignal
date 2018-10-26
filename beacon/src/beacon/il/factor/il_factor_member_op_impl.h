#ifndef BEACON_IL_IL_FACTOR_MEMBER_OP_H
#define BEACON_IL_IL_FACTOR_MEMBER_OP_H
#include "../../env/fqcn_cache.h"
#include "../../util/vector.h"
#include "../../util/string_pool.h"
#include "../../env/generic_cache.h"
#include "../il_factor_interface.h"

struct Enviroment;
struct Field;

/**
 * メンバアクセスを表す要素.
 */
typedef struct il_factor_member_op {
	il_factor* parent;
	il_factor* fact;
	StringView namev;
	Vector* type_args;
	int index;
	struct Field* f;
} il_factor_member_op;

il_factor* WrapILMemberOp(il_factor_member_op* self);

il_factor_member_op* NewILMemberOp(StringView namev);

void LoadILMemberOp(il_factor_member_op* self, Enviroment* env, CallContext* cctx);

void GenerateILMemberOp(il_factor_member_op* self, Enviroment* env, CallContext* cctx);

generic_type* EvalILMemberOp(il_factor_member_op* self, Enviroment* env, CallContext* cctx);

char* ILMemberOpToString(il_factor_member_op* self, Enviroment* env);

void DeleteILMemberOp(il_factor_member_op* self);

#endif