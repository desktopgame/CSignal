#include "call_context.h"
#include "../util/mem.h"
#include "../env/namespace.h"
#include "../env/method.h"
#include "../env/type_interface.h"
#include "../env/TYPE_IMPL.h"
#include "../env/generic_type.h"
#include "../env/fqcn_cache.h"

call_context* call_context_malloc(call_context_tag tag, const char* filename, int lineno) {
	call_context* ret = mem_malloc(sizeof(call_context), filename, lineno);
#if defined(_MSC_VER)
	control_structure cs = { 0 };
#else
	control_structure cs = {};
#endif
	ret->call_stack = MallocVector(filename, lineno);
	ret->scope = NULL;
	ret->ty = NULL;
	ret->tag = tag;
	ret->control = cs;
	control_structure_alloc(&ret->control);
	return ret;
}

call_frame* call_context_pushImpl(call_context* self, call_frame_tag tag, const char* filename, int lineno) {
	call_frame* fr = call_frame_malloc(tag, filename, lineno);
	PushVector(self->call_stack, fr);
	return fr;
}

call_frame* call_context_top(call_context* self) {
	return TopVector(self->call_stack);
}

void call_context_pop(call_context* self) {
	call_frame* fr = PopVector(self->call_stack);
	call_frame_delete(fr);
}

namespace_* call_context_namespace(call_context* self) {
	if(self->scope != NULL) {
		return self->scope;
	}
	return namespace_lang();
}

method* call_context_method(call_context* self) {
	if(self->tag != CALL_METHOD_T) {
		return NULL;
	}
	return self->u.mt;
}

type* call_context_type(call_context* self) {
	if(self->tag == CALL_TOP_T) {
		return namespace_get_type(namespace_lang(), InternString("World"));
	}
	return self->ty;
}

class_* call_context_class(call_context* self) {
	return TYPE2CLASS(call_context_type(self));
}

generic_type* call_context_receiver(call_context* self) {
	call_frame* cfr = TopVector(self->call_stack);
	if(cfr->tag == FRAME_INSTANCE_INVOKE_T) {
		return cfr->u.instance_invoke.receiver;
	} else if(cfr->tag == FRAME_SELF_INVOKE_T) {
		return self->ty->generic_self;
	} else if(cfr->tag == FRAME_RESOLVE_T) {
		return cfr->u.resolve.gtype;
	}
	return NULL;
}

type* call_context_eval_type(call_context* self, fqcn_cache* fqcn) {
	type* tp = fqcn_type(fqcn, self->scope);
	if(tp == NULL) {
		tp = fqcn_type(fqcn, namespace_lang());
	}
	return tp;
}

Vector* call_context_typeargs(call_context* self) {
	call_frame* cfr = TopVector(self->call_stack);
	if(cfr->tag == FRAME_INSTANCE_INVOKE_T) {
		return cfr->u.instance_invoke.typeargs;
	} else if(cfr->tag == FRAME_STATIC_INVOKE_T) {
		return cfr->u.static_invoke.typeargs;
	} else if(cfr->tag == FRAME_SELF_INVOKE_T) {
		return cfr->u.self_invoke.typeargs;
	} else if(cfr->tag == FRAME_RESOLVE_T) {
		return cfr->u.resolve.typeargs;
	}
	return NULL;
}

bool call_context_is_static(call_context* self) {
	return self->tag == CALL_METHOD_T &&
	       IsStaticModifier(self->u.mt->modifier);
}

void call_context_delete(call_context* self) {
	control_structure_free(self->control);
	DeleteVector(self->call_stack, VectorDeleterOfNull);
	MEM_FREE(self);
}