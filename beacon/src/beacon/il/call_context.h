#ifndef BEACON_IL_CALL_CONTEXT_H
#define BEACON_IL_CALL_CONTEXT_H
#include "../util/vector.h"
#include "call_frame.h"
#include "control_structure.h"
struct namespace_;
struct type;
struct class_;
struct method;
struct constructor;
struct operator_overload;
struct generic_type;
struct fqcn_cache;

typedef enum call_context_tag {
	//プログラムのトップレベル
	call_top_T,
	//メソッド
	call_method_T,
	//コンストラクタ
	call_ctor_T,
	//演算子オーバーロード
	call_opov_T,
	//コンストラクタの連鎖
	call_ctor_args_T,

	call_decl_T
} call_context_tag;

typedef struct call_context {
	vector* call_stack;
	control_structure control;
	call_context_tag tag;
	struct namespace_* scope;
	struct type* ty;
	union {
		struct method* mt;
		struct constructor* ctor;
		struct operator_overload* opov;
	} u;
} call_context;

#define call_context_new(tag) (call_context_malloc(tag, __FILE__, __LINE__))
call_context* call_context_malloc(call_context_tag tag, const char* filename, int lineno);

#define call_context_push(self, tag) (call_context_pushImpl(self, tag, __FILE__, __LINE__))
call_frame* call_context_pushImpl(call_context* self, call_frame_tag tag, const char* filename, int lineno);

call_frame* call_context_top(call_context* self);

void call_context_pop(call_context* self);

struct namespace_* call_context_namespace(call_context* self);

struct method* call_context_method(call_context* self);

struct type* call_context_type(call_context* self);

struct class_* call_context_class(call_context* self);

struct generic_type* call_context_receiver(call_context* self);

struct type* call_context_eval_type(call_context* self, struct fqcn_cache* fqcn);

vector* call_context_typeargs(call_context* self);

bool call_context_is_static(call_context* self);

void call_context_delete(call_context* self);
#endif