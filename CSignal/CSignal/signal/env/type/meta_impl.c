#include "meta_impl.h"
#include "../../il/il_argument.h"
#include "../parameter.h"

method * meta_find_method(vector * method_vec, const char * name, vector * args, enviroment * env, int * outIndex) {
	(*outIndex) = -1;
	//class_create_vtable(self);
	method* ret = NULL;
	int min = 1024;
	//	for (int i = 0; i < self->method_list->length; i++) {
	for (int i = 0; i < method_vec->length; i++) {
		//vector_item e = vector_at(self->method_list, i);
		vector_item e = vector_at(method_vec, i);
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
			score += type_distance(il_factor_eval(p->factor, env), p2->type);
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
