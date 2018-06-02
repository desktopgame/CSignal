#ifndef BEACON_IL_IL_FACTOR_MEMBER_OP_H
#define BEACON_IL_IL_FACTOR_MEMBER_OP_H
#include "../../env/fqcn_cache.h"
#include "../../util/vector.h"
#include "../../env/generic_cache.h"
#include "../il_factor_interface.h"

#define IL_FACT2MEM(fact) (il_factor_cast_member_op(fact))

struct enviroment;
struct field;

/**
 * メンバアクセスを表す要素.
 */
typedef struct il_factor_member_op {
	il_factor* fact;
	char* name;
	vector* type_args;
	int index;
	struct field* f;
} il_factor_member_op;

il_factor* il_factor_wrap_member_op(il_factor_member_op* self);

il_factor_member_op* il_factor_member_op_new(const char* name);

void il_factor_member_op_dump(il_factor_member_op* self, int depth);

void il_factor_member_op_load(il_factor_member_op* self, struct enviroment* env);

void il_factor_member_op_generate(il_factor_member_op* self, struct enviroment* env);

generic_type* il_factor_member_op_eval(il_factor_member_op* self, struct enviroment* env);

char* il_factor_member_op_tostr(il_factor_member_op* self, struct enviroment* env);

void il_factor_member_op_delete(il_factor_member_op* self);

il_factor_member_op* il_factor_cast_member_op(il_factor* fact);
#endif