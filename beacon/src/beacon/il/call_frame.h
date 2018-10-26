#ifndef BEACON_IL_CALL_FRAME_H
#define BEACON_IL_CALL_FRAME_H
#include "../util/vector.h"

struct Method;
struct Constructor;
struct OperatorOverload;
struct GenericType;

typedef enum CallFrameTag {
	FRAME_RESOLVE_T,
	FRAME_SELF_INVOKE_T,
	FRAME_STATIC_INVOKE_T,
	FRAME_INSTANCE_INVOKE_T,
} CallFrameTag;

typedef struct CallResolve {
	struct GenericType* GType;
	Vector* TypeArgs;
} CallResolve;

typedef struct CallSelfInvoke {
	Vector* Args;
	Vector* TypeArgs;
} CallSelfInvoke;

typedef struct CallStaticInvoke {
	Vector* Args;
	Vector* TypeArgs;
} CallStaticInvoke;

typedef struct CallInstanceInvoke {
	struct GenericType* Receiver;
	Vector* Args;
	Vector* TypeArgs;
} CallInstanceInvoke;

typedef struct CallFrame {
	CallFrameTag Tag;
	union {
		CallResolve Resolve;
		CallSelfInvoke SelfInvoke;
		CallStaticInvoke StaticInvoke;
		CallInstanceInvoke InstanceInvoke;
	} Kind;
} CallFrame;

#define NewCallFrame(tag) (MallocCallFrame(tag, __FILE__, __LINE__))
CallFrame* MallocCallFrame(CallFrameTag tag, const char* filename, int lineno);

void DeleteCallFrame(CallFrame* self);
#endif