#include "class.h"
#include "../util/text.h"
#include "../util/logger.h"
#include "parameter.h"
#include "../il/il_argument.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../util/mem.h"
#include "object.h"
#include "../vm/enviroment.h"
#include "../util/text.h"
#include "field.h"
#include "method.h"
#include "constructor.h"

//http://jumble-note.blogspot.jp/2012/09/c-vacopy.html
#ifndef va_copy
#    define va_copy(dest, src) ((dest) = (src))
#endif

//private
static void class_field_delete(vector_item item);
static void class_method_delete(vector_item item);
static vector * class_find_constructor_impl(class_ * self, vector * args, enviroment* env);

class_ * class_new(const char * name, class_type type) {
	assert(name != NULL);
	class_* ret = (class_*)MEM_MALLOC(sizeof(class_));
	ret->name = text_strdup(name);
	ret->type = type;
	ret->location = NULL;
	ret->state = class_none;
	ret->ref_count = 0;
	ret->super_class = NULL;
	ret->field_list = vector_new();
	ret->method_list = vector_new();
	ret->constructor_list = vector_new();
	ret->native_method_ref_map = tree_map_new();
	ret->absoluteIndex = -1;
	ret->vt = NULL;
	return ret;
}

void class_alloc_fields(class_ * self, object * o) {
	assert(o->type == object_ref);
	for (int i = 0; i < self->field_list->length; i++) {
		field* f = (field*)vector_at(self->field_list, i);
		if (modifier_is_static(f->modifier)) {
			continue;
		}
		object* a = object_ref_new();
		a->classz = f->type;
		vector_push(o->u.field_vec, a);
	}
	class_create_vtable(self->vt);
	o->classz = self;
	o->vptr = self->vt;
}

void class_free_fields(class_ * self, object * o) {
}

void class_dump(class_ * self, int depth) {
	text_putindent(depth);
	printf("class %s", self->name);
	text_putline();
	//フィールドの一覧をダンプ
	for (int i = 0; i < self->field_list->length; i++) {
		vector_item e = vector_at(self->field_list, i);
		field* f = (field*)e;
		field_dump(f, depth + 1);
	}
	//メソッドの一覧をダンプ
	for (int i = 0; i < self->method_list->length; i++) {
		vector_item e = vector_at(self->method_list, i);
		method* m = (method*)e;
		method_dump(m, depth + 1);
	}
	//コンストラクタの一覧をダンプ
	for (int i = 0; i < self->constructor_list->length; i++) {
		vector_item e = vector_at(self->constructor_list, i);
		constructor* c = (constructor*)e;
		constructor_dump(c, depth + 1);
	}
}

void class_define_native_method(class_ * self, const char * name, native_impl impl) {
	native_method_ref* ref = native_method_ref_new(impl);
	tree_map_put(self->native_method_ref_map, name, ref);
}

field * class_find_field(class_* self, const char * name, int* outIndex) {
	(*outIndex) = -1;
	for (int i = 0; i < self->field_list->length; i++) {
		vector_item e = vector_at(self->field_list, i);
		field* f = (field*)e;
		if (!strcmp(name, f->name)) {
			(*outIndex) = i;
			return f;
		}
	}
	return NULL;
}

field * class_find_field_tree(class_ * self, const char * name, access_domain domain, int * outIndex) {
	class_* pointee = self;
	do {
		field* f = class_find_field(pointee, name, outIndex);
		if (f != NULL && domain_accept(domain, f->modifier, f->access)) {
			return f;
		}
		pointee = pointee->super_class;
	} while (pointee != NULL);
	return NULL;
}

constructor * class_find_constructor(class_ * self, vector * args, enviroment * env, int* outIndex) {
	vector* v = class_find_constructor_impl(self, args, env);
	(*outIndex) = -1;
	//コンストラクタが一つも見つからなかった
	if (v->length == 0) {
		vector_delete(v, vector_deleter_null);
		return NULL;
	}
	//見つかった中からもっとも一致するコンストラクタを選択する
	int min = 1024;
	constructor* ret = NULL;
	for (int i = 0; i < v->length; i++) {
		vector_item e = vector_at(v, i);
		constructor* c = (constructor*)e;
		int score = 0;
		for (int j = 0; j < c->parameter_list->length; j++) {
			vector_item d = vector_at(args, j);
			vector_item d2 = vector_at(c->parameter_list, j);
			il_argument* p = (il_argument*)d;
			parameter* p2 = (parameter*)d2;
			score += class_distance(il_factor_eval(p->factor, env), p2->classz);
		}
		if (score < min) {
			min = score;
			ret = c;
			(*outIndex) = i;
		}
	}
	vector_delete(v, vector_deleter_null);
	return ret;
}

method * class_find_method(class_ * self, const char * name, vector * args, enviroment * env, int * outIndex) {
	//vector* v = class_find_method_impl(self, name, args, env);
	(*outIndex) = -1;
	class_create_vtable(self);
	method* ret = NULL;
	int min = 1024;
	//	for (int i = 0; i < self->method_list->length; i++) {
	for (int i = 0; i < self->vt->elements->length; i++) {
		//vector_item e = vector_at(self->method_list, i);
		vector_item e = vector_at(self->vt->elements, i);
		method* m = (method*)e;
		//名前か引数の個数が違うので無視
		if (strcmp(m->name, name) ||
			m->parameter_list->length != args->length
			) {
			continue;
		}
		//引数がひとつもないので、
		//型のチェックを行わない
		if (args->length == 0) {
			(*outIndex) = i;
			return m;
		}
		int score = 0;
		for (int j = 0; j < m->parameter_list->length; j++) {
			vector_item d = vector_at(args, j);
			vector_item d2 = vector_at(m->parameter_list, j);
			il_argument* p = (il_argument*)d;
			parameter* p2 = (parameter*)d2;
			score += class_distance(il_factor_eval(p->factor, env), p2->classz);
		}
		if (score < min) {
			//TEST(env->toplevel);
			min = score;
			ret = m;
			(*outIndex) = i;
		}
	}
	return ret;
}

int class_field_index_resolve(class_ * self, int index) {
	assert(index >= 0);
	if (self->super_class == NULL) {
		return index;
	}
	class_* pointee = self->super_class;
	do {
		index += (pointee->field_list->length);
		pointee = pointee->super_class;
	} while (pointee != NULL);
	return index;
}

field * class_field_by_index(class_ * self, int index) {
	if (self->super_class == NULL) {
		vector_item e = vector_at(self->field_list, index);
		return (field*)e;
	}
	class_* pointee = self;
	do {
		int length = pointee->field_list->length;
		int end = class_field_countall(pointee);
		int start = end - length;
		int relative = index - start;
		if (index >= start && index < end) {
			vector_item e = vector_at(pointee->field_list, relative);
			return (field*)e;
		}
		pointee = pointee->super_class;
	} while (pointee != NULL);
	return NULL;
}

int class_field_countall(class_ * self) {
	return class_field_index_resolve(self, self->field_list->length);
}

bool class_castable(class_ * self, class_ * other) {
	assert(self != NULL && other != NULL);
	if (self == other) {
		return true;
	}
	class_* pointee = self;
	do {
		if (pointee == other) {
			return true;
		}
		pointee = pointee->super_class;
	} while (pointee != NULL);
	return false;
}

int class_distance(class_ * self, class_ * other) {
	if (self == other) {
		return 0;
	}
	int depth = 0;
	class_* pointee = self;
	do {
		if (pointee == other) {
			return depth;
		}
		pointee = pointee->super_class;
		depth++;
		if (pointee == NULL) {
			depth = -1;
			break;
		}
	} while (1);
	return depth;
}

void class_create_vtable(class_ * self) {
	assert(self != NULL);
	//初期化済み
	if (self->vt != NULL) {
		return;
	}
	self->vt = vtable_new();
	//トップレベルではメソッドの一覧を配列に入れるだけ
	if (self->super_class == NULL) {
		for (int i = 0; i < self->method_list->length; i++) {
			vector_push(self->vt->elements, vector_at(self->method_list, i));
		}
	//あるクラスを継承する場合には、
	//重複するメソッドを上書きするように
	} else {
		class_create_vtable(self->super_class);
		vtable_copy(self->super_class->vt, self->vt);
		for (int i = 0; i < self->method_list->length; i++) {
			method* m = (method*)vector_at(self->method_list, i);
			vtable_replace(self->vt, m);
		}
	}
}

void class_linkall(class_ * self) {
	for (int i = 0; i < self->field_list->length; i++) {
		field* f = (field*)vector_at(self->field_list, i);
		f->parent = self;
	}
	for (int i = 0; i < self->method_list->length; i++) {
		method* m = (method*)vector_at(self->method_list, i);
		m->parent = self;
	}
}

void class_delete(class_ * self) {
	assert(self->ref_count == 0);
	MEM_FREE(self->name);
	if (self->super_class != NULL) {
		self->super_class->ref_count--;
	}
	vector_delete(self->field_list, class_field_delete);
	vector_delete(self->method_list, class_method_delete);
	MEM_FREE(self);
}

//private
static void class_field_delete(vector_item item) {
	field* e = (field*)item;
	field_delete(e);
}

static void class_method_delete(vector_item item) {
	method* e = (method*)item;
	method_delete(e);
}

static vector * class_find_constructor_impl(class_ * self, vector * args, enviroment* env) {
	vector* v = vector_new();
	if (self == NULL) {
		return v;
	}
	for (int i = 0; i < self->constructor_list->length; i++) {
		vector_item e = vector_at(self->constructor_list, i);
		constructor* c = (constructor*)e;
		//引数の個数が違うので無視
		if (c->parameter_list->length != args->length) {
			continue;
		}
		//引数がひとつもないので、
		//型のチェックを行わない
		if (args->length == 0) {
			vector_push(v, c);
			continue;
		}
		bool match = true;
		for (int j = 0; j < args->length; j++) {
			vector_item d = vector_at(args, j);
			vector_item d2 = vector_at(c->parameter_list, j);
			il_argument* p = (il_argument*)d;
			parameter* p2 = (parameter*)d2;
			if (!class_castable(il_factor_eval(p->factor, env), p2->classz)) {
				match = false;
				break;
			}
		}
		if (match) {
			vector_push(v, c);
		}
	}
	return v;
}
