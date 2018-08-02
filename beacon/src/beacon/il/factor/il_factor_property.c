#include "il_factor_property.h"
#include "../../util/mem.h"
#include "../../vm/enviroment.h"
#include "../../env/generic_type.h"
#include "../../env/field.h"
#include "../../env/type_impl.h"
#include <assert.h>

static void il_factor_generate_field(il_factor_property* self, enviroment* env, call_context* cctx);
static void il_factor_generate_property(il_factor_property* self, enviroment* env, call_context* cctx);


il_factor_property* il_factor_property_malloc(const char* filename, int lineno) {
	il_factor_property* ret = mem_malloc(sizeof(il_factor_property), filename, lineno);
	ret->fact = NULL;
	ret->index = -1;
	ret->namev = ZERO_VIEW;
	ret->p = NULL;
	return ret;
}

void il_factor_property_generate(il_factor_property* self, enviroment* env, call_context* cctx) {
	if(!self->p->is_short) {
		il_factor_generate_property(self, env, cctx);
	} else {
		il_factor_generate_field(self, env, cctx);
	}
}

void il_factor_property_load(il_factor_property* self, enviroment* env, call_context* cctx) {
	generic_type* receiver = il_factor_eval(self->fact, env, cctx);
	type* receiverT = GENERIC2TYPE(receiver);
	if(self->p->is_short) {
		int temp = -1;
		class_find_property_tree(TYPE2CLASS(receiverT), self->p->namev, &temp);
		assert(temp != -1);
		self->index = temp;
	} else {
		self->index = -1;
	}
}

generic_type* il_factor_property_eval(il_factor_property* self, enviroment* env, call_context* cctx) {
	return self->p->gtype;
}

char* il_factor_property_tostr(il_factor_property* self, enviroment* env) {
	string_buffer* sb = string_buffer_new();
	char* name = il_factor_tostr(self->fact, env);
	string_buffer_appends(sb, name);
	string_buffer_append(sb, '.');
	string_buffer_appends(sb, string_pool_ref2str(self->namev));
	MEM_FREE(name);
	return string_buffer_release(sb);
}

void il_factor_property_dump(il_factor_property* self, int depth) {

}

void il_factor_property_delete(il_factor_property* self) {
	il_factor_delete(self->fact);
	MEM_FREE(self);
}
//private
static void il_factor_generate_field(il_factor_property* self, enviroment* env, call_context* cctx) {
	field* f = self->p->source_ref;
	if(modifier_is_static(f->modifier)) {
		opcode_buf_add(env->buf, op_get_static);
		opcode_buf_add(env->buf, f->parent->absolute_index);
		opcode_buf_add(env->buf, class_get_field_by_property(TYPE2CLASS(self->p->parent), self->p));
	} else {
		il_factor_generate(self->fact, env, cctx);
		opcode_buf_add(env->buf, op_get_field);
		opcode_buf_add(env->buf, class_get_field_by_property(TYPE2CLASS(self->p->parent), self->p));
	}
}

static void il_factor_generate_property(il_factor_property* self, enviroment* env, call_context* cctx) {
	if(modifier_is_static(self->p->modifier)) {
		opcode_buf_add(env->buf, op_get_static_property);
		opcode_buf_add(env->buf, self->p->parent->absolute_index);
		opcode_buf_add(env->buf, self->index);
	} else {
		il_factor_generate(self->fact, env, cctx);
		opcode_buf_add(env->buf, op_get_property);
		opcode_buf_add(env->buf, self->index);
	}
}