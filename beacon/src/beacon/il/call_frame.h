#ifndef BEACON_IL_CALL_FRAME_H
#define BEACON_IL_CALL_FRAME_H
#include "../util/vector.h"
struct method;
struct constructor;
struct operator_overload;

typedef enum call_frame_tag {
	call_top_T,
	call_method_T,
	call_ctor_T,
	call_opov_T,
} call_frame_tag;

typedef struct call_frame {
	vector* typeargs;
	call_frame_tag tag;
	union {
		struct method* m;
		struct constructor* ctor;
		struct operator_overload* opov;
	} u;
} call_frame;

#define call_frame_new(tag) (call_frame_malloc(tag, __FILE__, __LINE__))
call_frame* call_frame_malloc(call_frame_tag tag, const char* filename, int lineno);

void call_frame_delete(call_frame* self);
#endif