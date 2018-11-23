// BEGIN-AUTOGENERATED-BLOCK
/**
 * @file call_frame.h
 * @brief ここに概要を記述します
 * @author koya
 * @date 2018/10/31
 */
// END-AUTOGENERATED-BLOCK

#ifndef BEACON_IL_CALL_FRAME_H
#define BEACON_IL_CALL_FRAME_H
#include "../util/vector.h"

struct bc_Method;
struct bc_Constructor;
struct bc_OperatorOverload;
struct bc_GenericType;

typedef enum bc_CallFrameTag {
        FRAME_RESOLVE_T,
        FRAME_SELF_INVOKE_T,
        FRAME_STATIC_INVOKE_T,
        FRAME_INSTANCE_INVOKE_T,
} bc_CallFrameTag;

typedef struct bc_CallResolve {
        struct bc_GenericType* GType;
        bc_Vector* TypeArgs;
} bc_CallResolve;

typedef struct bc_CallSelfInvoke {
        bc_Vector* Args;
        bc_Vector* TypeArgs;
} bc_CallSelfInvoke;

typedef struct bc_CallStaticInvoke {
        bc_Vector* Args;
        bc_Vector* TypeArgs;
} bc_CallStaticInvoke;

typedef struct bc_CallInstanceInvoke {
        struct bc_GenericType* Receiver;
        bc_Vector* Args;
        bc_Vector* TypeArgs;
} bc_CallInstanceInvoke;

typedef struct bc_CallFrame {
        bc_CallFrameTag Tag;
        union {
                bc_CallResolve Resolve;
                bc_CallSelfInvoke SelfInvoke;
                bc_CallStaticInvoke StaticInvoke;
                bc_CallInstanceInvoke InstanceInvoke;
        } Kind;
} bc_CallFrame;

#define bc_NewCallFrame(tag) (bc_MallocCallFrame(tag, __FILE__, __LINE__))
bc_CallFrame* bc_MallocCallFrame(bc_CallFrameTag tag, const char* filename,
                                 int lineno);

void bc_DeleteCallFrame(bc_CallFrame* self);
#endif