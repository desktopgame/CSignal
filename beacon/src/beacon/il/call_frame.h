#ifndef BEACON_IL_CALL_FRAME_H
#define BEACON_IL_CALL_FRAME_H
#include "../util/vector.h"

struct method;
struct constructor;
struct operator_overload;
struct generic_type;

typedef enum call_frame_tag {
	frame_resolve_T,
	frame_self_invoke_T,
	frame_static_invoke_T,
	frame_instance_invoke_T,
} call_frame_tag;

typedef struct call_resolve {
	struct generic_type* gtype;
	vector* typeargs;
} call_resolve;

typedef struct call_self_invoke {
	vector* args;
	vector* typeargs;
} call_self_invoke;

typedef struct call_static_invoke {
	vector* args;
	vector* typeargs;
} call_static_invoke;

typedef struct call_instance_invoke {
	struct generic_type* receiver;
	vector* args;
	vector* typeargs;
} call_instance_invoke;

typedef struct call_frame {
	call_frame_tag tag;
	union {
		call_resolve resolve;
		call_self_invoke self_invoke;
		call_static_invoke static_invoke;
		call_instance_invoke instance_invoke;
	} u;
} call_frame;

#define call_frame_new(tag) (call_frame_malloc(tag, __FILE__, __LINE__))
call_frame* call_frame_malloc(call_frame_tag tag, const char* filename, int lineno);

void call_frame_delete(call_frame* self);
#endif