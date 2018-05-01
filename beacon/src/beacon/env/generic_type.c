#include "generic_type.h"
#include "type_interface.h"
#include "type_impl.h"
#include "script_context.h"
#include "type_parameter.h"
#include "constructor.h"
#include "../util/mem.h"
#include "../util/text.h"
#include "../util/xassert.h"
#include "../il/il_type_argument.h"
#include "fqcn_cache.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>

//proto
static void generic_type_delete_self(vector_item item);
static void generic_type_deletercr_self(vector_item item);
static void generic_type_recursive_mark(generic_type* a);
static generic_type* generic_type_get(generic_type* a, il_context* ilctx);
/*
generic_type * generic_type_new(type * core_type) {

}
*/

generic_type* generic_type_validate(generic_type* self) {
//	#if defined(VSCDEBUG)
	assert(self != NULL);
	assert((self)->core_type != NULL || self->virtual_type_index != -1);
	for(int i=0; i<self->type_args_list->length; i++) {
		generic_type_validate((generic_type*)vector_at(self->type_args_list, i));
	}
	return self;
//	#endif
}

generic_type* generic_type_make(type* core_type) {
	/*
	if(core_type == NULL) {
		return generic_type_new(core_type);
	}
	generic_type* ret = generic_type_new(core_type);
	int len = type_type_parameter_len(core_type);
	for(int i=0; i<len; i++) {
		generic_type* a = generic_type_new(NULL);
		a->tag = generic_type_tag_class;
		a->virtual_type_index = i;
		a->u.type_ = core_type;
		generic_type_addargs(ret, a);
	}
	if(core_type->tag == type_class &&
	   !strcmp(core_type->u.class_->name, "Array")) {
		assert((len == 1));
	}
	return ret;
	*/
	if(core_type == NULL) {
		return generic_type_new(core_type);
	}
	return core_type->generic_self;
}

generic_type* generic_type_malloc(struct type* core_type, const char* filename, int lineno) {
	generic_type* ret = (generic_type*)mem_malloc(sizeof(generic_type), filename, lineno);
	ret->core_type = core_type;
	ret->type_args_list = vector_new();
	ret->virtual_type_index = -1;
	ret->tag = generic_type_tag_none;
	//現在のスクリプトコンテキストに登録
	script_context* ctx = script_context_get_current();
	vector_push(ctx->all_generic_vec, ret);
	return ret;
}

void generic_type_collect() {
	script_context* ctx = script_context_get_current();
	//マークを外す
	for(int i=0; i<ctx->all_generic_vec->length; i++) {
		generic_type* e= (generic_type*)vector_at(ctx->all_generic_vec, i);
		e->mark = false;
	}
	//全ての型に定義された自身を参照するための generic をマーク
	for(int i=0; i<ctx->type_vec->length; i++) {
		type* e= (type*)vector_at(ctx->type_vec, i);
		generic_type_recursive_mark(e->generic_self);
	}
	vector* alive = vector_new();
	vector* dead = vector_new();
	for(int i=0; i<ctx->all_generic_vec->length; i++) {
		generic_type* e= (generic_type*)vector_at(ctx->all_generic_vec, i);
		vector_push((!e->mark ? dead : alive), e);
	}
	vector_delete(ctx->all_generic_vec, vector_deleter_null);
	vector_delete(dead, generic_type_delete_self);
	ctx->all_generic_vec = alive;
}

void generic_type_lostownership(generic_type* a) {
	assert(a->core_type != NULL);
	assert(a->core_type->generic_self == a);
	generic_type_deletercr_self(a);
}

void generic_type_addargs(generic_type* self, generic_type* a) {
	assert(a != NULL);
	generic_type_validate(a);
	vector_push(self->type_args_list, a);
}

int generic_type_distance(generic_type * self, generic_type * other, il_context* ilctx) {
	//要求されている型は T
	if(self->core_type == NULL) {
		//提供されているのは T
		if(other->core_type == NULL) {
			if(generic_type_rule_valid(generic_type_rule(self, ilctx), generic_type_rule(other, ilctx))) {
				return 0;
			} else return -1;
		//提供されているのは具体的な型
		} else {
			//具体的な型が T のルールを満たしているか？
			if(generic_type_rule_test(other, generic_type_rule(self, ilctx), ilctx)) {
				return 0;
			} else return -1;
		}
	//提供している型は T
	} else if(other->core_type == NULL) {
		//要求されているのは具体的な型
		if(self->core_type != NULL) {
			//T が 具体的な型の要件を満たしているか？
			if(self->core_type == CL_OBJECT ||
				generic_type_rule_polymorphic(generic_type_rule(other, ilctx), self, ilctx)) {
				return 0;
			} else return -1;
		//要求されているのは T
		} else {
			if(generic_type_rule_valid(generic_type_rule(self, ilctx), generic_type_rule(other, ilctx))) {
				return 0;
			} else return -1;
		}
	//どちらも具体的な型
	} else {
		int dist = type_distance(self->core_type, other->core_type);
		assert(self->core_type != NULL);
		assert(other->core_type != NULL);
		//List : Dict みたいな型ならもうこの時点で次へ
		if(dist == -1) {
			return dist;
		}
		//otherからselfまで辿る
		class_* baseline = self->core_type->u.class_;
		class_* ptr = other->core_type->u.class_;
		generic_type* target = other;
		while(baseline != ptr) {
			target = ptr->super_class;
			ptr = ptr->super_class->core_type->u.class_;
		}
		assert(target != NULL);
		assert(self->type_args_list->length == target->type_args_list->length);
		for(int i=0; i<self->type_args_list->length; i++) {
			generic_type* a = vector_at(self->type_args_list, i);
			generic_type* b = vector_at(target->type_args_list, i);
			int calc = generic_type_distance(a, b, ilctx);
			if(calc == -1) {
				dist = -1;
				break;
			}
		}
		return dist;
	}
}

void generic_type_print(generic_type * self) {
	assert(self != NULL);
	if (self->virtual_type_index != -1) {
		text_printf("[%d]", self->virtual_type_index);
	} else {
		text_printf("%s", type_name(self->core_type));
	}
	if (self->type_args_list->length == 0) {
		return;
	}
	text_printf("<");
	for (int i = 0; i < self->type_args_list->length; i++) {
		generic_type* e = (generic_type*)vector_at(self->type_args_list, i);
		generic_type_print(e);
		if (i != self->type_args_list->length - 1) {
			text_printf(",");
		}
	}
	text_printf(">");
}

bool generic_type_int(generic_type* self) {
	return self->core_type == CL_INT;
}

bool generic_type_double(generic_type* self) {
	return self->core_type == CL_DOUBLE;
}

bool generic_type_bool(generic_type* self) {
	return self->core_type == CL_BOOL;
}

//Hash<String,List<Int>>
generic_type* generic_type_apply(generic_type* self, il_context* ilctx) {
	//ここで型変数が追加されちゃってた
	if(self->core_type == NULL) {
		//copy->virtual_type_index = -1;
		if(self->tag == generic_type_tag_ctor) {
			vector* type_args = vector_top(ilctx->type_args_vec);
			il_type_argument* a = vector_at(type_args, self->virtual_type_index);
			//copy->core_type = a->gtype->core_type;
			self = a->gtype;
		}
	}
	generic_type* copy = generic_type_new(self->core_type);
	generic_type* e = NULL;
	int count = 0;
	//全ての実型引数
	for(int i=0; i<self->type_args_list->length; i++) {
		e = (generic_type*)vector_at(self->type_args_list, i);
		//この型がクラスやメソッドに定義された仮装型なら
		if(e->virtual_type_index != -1) {
			count++;
			if(e->tag == generic_type_tag_class) {
				generic_type* tp = vector_top(ilctx->receiver_vec);
				generic_type* instanced = vector_at(tp->type_args_list, e->virtual_type_index);
				generic_type_addargs(copy, generic_type_apply(instanced, ilctx));
			} else if(e->tag == generic_type_tag_method ||
			e->tag == generic_type_tag_ctor) {
				vector* type_args = vector_top(ilctx->type_args_vec);
				//generic_type* a = vector_at(type_args, e->virtual_type_index);
				il_type_argument* a = vector_at(type_args, e->virtual_type_index);
				generic_type_addargs(copy, generic_type_apply(a->gtype, ilctx));
			} else if(e->tag == generic_type_tag_self) {
				generic_type_addargs(copy, e);
			} else XBREAK(e->tag != generic_type_tag_none);
		//
		} else {
			generic_type_addargs(copy, generic_type_apply(e, ilctx));
		}
	}
	assert(copy->core_type != NULL || count == 0);
	copy->tag = generic_type_tag_none;
	
	if(copy->core_type == NULL) {
		copy->tag = self->tag;
		copy->virtual_type_index = self->virtual_type_index;
		if(self->tag == generic_type_tag_class) copy->u.type_ = self->u.type_;
		else if (self->tag == generic_type_tag_method) copy->u.method_ = self->u.method_;
	}
	return copy;
}

vector* generic_type_rule(generic_type* self, il_context* ilctx) {
	if(self->core_type != NULL) {
		return NULL;
	}
	if(self->tag == generic_type_tag_class ||
	self->tag == generic_type_tag_self ||
	self->tag == generic_type_tag_ctor) {
		type* tp = NULL;
		//コンストラクタを検索している場合は
		//特別扱い
		if(ilctx->find_static > ilctx->find_instance) {
			tp = (type*)vector_top(ilctx->type_vec);
			assert(tp != NULL);
		} else {
			generic_type* gt = (generic_type*)vector_top(ilctx->receiver_vec);
			tp = gt->core_type;
		}
		//type* tp = self->core_type;
		vector* params = type_parameter_list(tp);
		type_parameter* param = vector_at(params, self->virtual_type_index);
		return param->rule_vec;
	} else if(self->tag == generic_type_tag_method) {
		method* m = (method*)vector_top(ilctx->method_vec);
		vector* params = m->type_parameter_list;
		type_parameter* param = vector_at(params, self->virtual_type_index);
		return param->rule_vec;
	}
	assert(false);
	return NULL;
}

bool generic_type_rule_valid(vector* self, vector* other) {
	assert(self != NULL);
	assert(other != NULL);
	if(other->length == 0) {
		return true;
	}
	bool valid = true;
	//満たすべきルール全て
	for(int i=0; i<other->length; i++) {
		type_parameter_rule* otherR = vector_at(other, i);
		//満たすべきルールの中に newable を見つけたなら
		//self にもそれが必要
		if(otherR->tag == type_parameter_rule_tag_neweable) {
			for(int j=0; j<self->length; j++) {
				type_parameter_rule* selfR = vector_at(self, j);
				if(selfR->tag == type_parameter_rule_tag_neweable) {
					break;
				}
			}
		//満たすべきルールの中に polymorphic を見つけたなら
		//self にもそれが必要
		} else if(otherR->tag == type_parameter_rule_tag_polymorphic) {
			//未実装
			assert(false);
		}
	}
	return valid;
}

bool generic_type_rule_test(generic_type* self, vector* rules, il_context* ilctx) {
	assert(self != NULL);
	assert(rules != NULL);
	if(rules->length == 0) {
		return true;
	}
	bool valid = true;
	for(int i=0; i<rules->length; i++) {
		type_parameter_rule* r = vector_at(rules, i);
		if(r->tag == type_parameter_rule_tag_neweable) {

		} else if(r->tag == type_parameter_rule_tag_polymorphic) {
			generic_type* protocol = r->u.gtype_;
			if(generic_type_distance(self, protocol, ilctx) == -1) {
				valid = false;
				break;
			}
		}
	}
	return valid;
}

bool generic_type_rule_polymorphic(vector* rules, generic_type* other, il_context* ilctx) {
	assert(rules != NULL);
	assert(other != NULL);
	if(rules->length == 0) {
		return false;
	}
	bool valid = false;
	for(int i=0; i<rules->length; i++) {
		type_parameter_rule* r = vector_at(rules, i);
		if(r->tag == type_parameter_rule_tag_polymorphic) {
			generic_type* protocol = r->u.gtype_;
			if(generic_type_distance(other, protocol, ilctx) != -1) {
				valid = true;
				break;
			}
		}
	}
	return valid;
}

//private
static generic_type* generic_type_get(generic_type* a, il_context* ilctx) {
	if(a->virtual_type_index == -1) {
		return a;
	}
	if(a->tag == generic_type_tag_class) {
		generic_type* receiver = vector_at(ilctx->receiver_vec, a->virtual_type_index);
		a = receiver;
	} else if(a->tag == generic_type_tag_method) {
		generic_type* at = vector_at(ilctx->type_args_vec, a->virtual_type_index);
		a = at;
	}
	return a;
}

static void generic_type_delete_self(vector_item item) {
	generic_type* e = (generic_type*)item;
	vector_delete(e->type_args_list, vector_deleter_null);
	MEM_FREE(e);
}

static void generic_type_deletercr_self(vector_item item) {
	generic_type* e = (generic_type*)item;
	vector_delete(e->type_args_list, generic_type_deletercr_self);
	MEM_FREE(e);
}

static void generic_type_recursive_mark(generic_type* a) {
	if(a == NULL || a->mark) {
		return;
	}
	a->mark = true;
	for(int i=0; i<a->type_args_list->length; i++) {
		generic_type_recursive_mark((generic_type*)vector_at(a->type_args_list, i));
	}
}