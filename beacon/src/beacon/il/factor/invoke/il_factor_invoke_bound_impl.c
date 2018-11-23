#include "il_factor_invoke_bound_impl.h"
#include "../../../util/mem.h"
#include "../../../util/text.h"
#include "../../../env/field.h"
#include "../../../env/property.h"
#include "../../../env/operator_overload.h"
#include "../../../env/generic_type.h"
#include "../../../env/type_interface.h"
#include "../../../env/type/class_impl.h"
#include "../../../vm/symbol_entry.h"
#include "../../../vm/enviroment.h"
#include "../../il_argument.h"
#include "../../il_type_argument.h"

//proto
static void DeleteILInvokeBound_typeargs(bc_VectorItem item);
static void resolve_non_default(bc_ILInvokeBound * self, bc_Enviroment * env, bc_CallContext* cctx);
static void resolve_default(bc_ILInvokeBound * self, bc_Enviroment * env, bc_CallContext* cctx);
static void ILInvokeBound_check(bc_ILInvokeBound * self, bc_Enviroment * env, bc_CallContext* cctx);
static void ILInvokeBound_args_delete(bc_VectorItem item);
static void GenerateILInvokeBound_method(bc_ILInvokeBound* self, bc_Enviroment* env, bc_CallContext* cctx);
static void GenerateILInvokeBound_subscript(bc_ILInvokeBound* self, bc_Enviroment* env, bc_CallContext* cctx);
static bc_GenericType* ILInvokeBound_return_gtype(bc_ILInvokeBound* self, bc_CallContext* cctx);
static bc_GenericType* EvalILInvokeBoundImpl(bc_ILInvokeBound * self, bc_Enviroment * env, bc_CallContext* cctx);

bc_ILInvokeBound* bc_NewILInvokeBound(bc_StringView namev) {
	bc_ILInvokeBound* ret = (bc_ILInvokeBound*)MEM_MALLOC(sizeof(bc_ILInvokeBound));
	ret->Name = namev;
	ret->Arguments = NULL;
	ret->TypeArgs = NULL;
	ret->Index = -1;
	ret->Resolved = NULL;
	ret->Tag = BOUND_INVOKE_UNDEFINED_T;
	return ret;
}

void bc_GenerateILInvokeBound(bc_ILInvokeBound* self, bc_Enviroment* env, bc_CallContext* cctx) {
	GenerateILInvokeBound_method(self, env, cctx);
	GenerateILInvokeBound_subscript(self, env, cctx);
}

void bc_LoadILInvokeBound(bc_ILInvokeBound * self, bc_Enviroment * env, bc_CallContext* cctx) {
	ILInvokeBound_check(self, env, cctx);
}

bc_GenericType* bc_EvalILInvokeBound(bc_ILInvokeBound * self, bc_Enviroment * env, bc_CallContext* cctx) {
	bc_GenericType* ret = EvalILInvokeBoundImpl(self, env, cctx);
	assert(ret != NULL);
	return ret;
}

char* bc_ILInvokeBoundToString(bc_ILInvokeBound* self, bc_Enviroment* env) {
	bc_Buffer* sb = bc_NewBuffer();
	bc_AppendsBuffer(sb, bc_Ref2Str(self->Name));
	bc_ILTypeArgsToString(sb, self->TypeArgs, env);
	bc_ILArgsToString(sb, self->TypeArgs, env);
	return bc_ReleaseBuffer(sb);
}

void bc_DeleteILInvokeBound(bc_ILInvokeBound* self) {
	bc_DeleteVector(self->Arguments, ILInvokeBound_args_delete);
	bc_DeleteVector(self->TypeArgs, DeleteILInvokeBound_typeargs);
	//generic_DeleteType(self->Resolved);
	MEM_FREE(self);
}

bc_OperatorOverload* bc_FindSetILInvokeBound(bc_ILInvokeBound* self, bc_ILFactor* value, bc_Enviroment* env, bc_CallContext* cctx, int* outIndex) {
	assert(self->Tag == BOUND_INVOKE_SUBSCRIPT_T);
	bc_Vector* args = bc_NewVector();
	bc_PushVector(args, ((bc_ILArgument*)bc_AtVector(self->Arguments, 0))->Factor);
	bc_PushVector(args, value);
	bc_OperatorOverload* opov = bc_ILFindOperatorOverloadClass(BC_TYPE2CLASS(self->Kind.Subscript.Operator->Parent), OPERATOR_SUB_SCRIPT_SET_T, args, env, cctx, outIndex);
	bc_DeleteVector(args, bc_VectorDeleterOfNull);
	return opov;
}

//private
//FIXME:ILInvokeからのコピペ
static void DeleteILInvokeBound_typeargs(bc_VectorItem item) {
	bc_ILTypeArgument* e = (bc_ILTypeArgument*)item;
	bc_DeleteILTypeArgument(e);
}

static void resolve_non_default(bc_ILInvokeBound * self, bc_Enviroment * env, bc_CallContext* cctx) {
	if(self->Resolved != NULL) {
		return;
	}
	bc_Type* tp = NULL;
	bc_GenericType* rgtp  = ILInvokeBound_return_gtype(self, cctx);
	if(rgtp->Tag == GENERIC_TYPE_TAG_CLASS_T) {
		self->Resolved = bc_NewGenericType(NULL);
		self->Resolved->Tag = GENERIC_TYPE_TAG_CLASS_T;
		self->Resolved->VirtualTypeIndex = rgtp->VirtualTypeIndex;
	} else if(rgtp->Tag == GENERIC_TYPE_TAG_METHOD_T) {
		//メソッドに渡された型引数を参照する
		bc_GenericType* instanced_type = (bc_GenericType*)bc_AtVector(self->TypeArgs, rgtp->VirtualTypeIndex);
		self->Resolved = bc_NewGenericType(instanced_type->CoreType);
		self->Resolved->Tag = GENERIC_TYPE_TAG_CLASS_T;
	}
}

static void resolve_default(bc_ILInvokeBound * self, bc_Enviroment * env, bc_CallContext* cctx) {
	if(self->Resolved != NULL) {
		return;
	}
	bc_GenericType* rgtp = ILInvokeBound_return_gtype(self, cctx);
	self->Resolved = bc_ApplyGenericType(rgtp, cctx);
}

static void ILInvokeBound_check(bc_ILInvokeBound * self, bc_Enviroment * env, bc_CallContext* cctx) {
	if(self->Index != -1) {
		return;
	}
	//対応するメソッドを検索
	bc_Type* ctype = bc_GetTypeCContext(cctx);
	int temp = -1;
	bc_ResolveILTypeArgument(self->TypeArgs, cctx);
	for(int i=0; i<self->Arguments->Length; i++) {
		bc_ILArgument* ilarg = bc_AtVector(self->Arguments, i);
		bc_LoadILFactor(ilarg->Factor, env, cctx);
	}
	BC_ERROR();
	#if defined(DEBUG)
	const char* nstr = bc_Ref2Str(self->Name);
	const char* str = bc_Ref2Str(bc_GetTypeName(ctype));
	#endif
	bc_CallFrame* cfr = bc_PushCallContext(cctx, FRAME_SELF_INVOKE_T);
	cfr->Kind.SelfInvoke.Args = self->Arguments;
	cfr->Kind.SelfInvoke.TypeArgs = self->TypeArgs;
	self->Tag = BOUND_INVOKE_METHOD_T;
	self->Kind.Method = bc_ILFindMethodClass(BC_TYPE2CLASS(ctype), self->Name, self->Arguments, env, cctx, &temp);
	self->Index = temp;
	BC_ERROR();
	if(self->Index != -1) {
		bc_PopCallContext(cctx);
		return;
	}
	//添字アクセスとして解決する
	bc_GenericType* receiver_gtype = NULL;
	bc_SymbolEntry* local = bc_EntrySymbolTable(env->Symboles, NULL, self->Name);
	if(receiver_gtype == NULL && local != NULL) {
		receiver_gtype = local->GType;
		self->Kind.Subscript.Tag = SUBSCRIPT_LOCAL_T;
		self->Kind.Subscript.Kind.Local = local;
		self->Kind.Subscript.Index = local->Index;
	}
	//フィールドとして解決する
	bc_Field* fi = bc_FindFieldClass(bc_GetClassCContext(cctx), self->Name, &temp);
	if(receiver_gtype == NULL && fi != NULL) {
		receiver_gtype = fi->GType;
		self->Kind.Subscript.Tag = SUBSCRIPT_FIELD_T;
		self->Kind.Subscript.Kind.Field = fi;
		self->Kind.Subscript.Index = temp;
	}
	//プロパティとして解決する
	bc_Property* prop = bc_FindPropertyClass(bc_GetClassCContext(cctx), self->Name, &temp);
	if(receiver_gtype == NULL && prop != NULL) {
		receiver_gtype = prop->GType;
		self->Kind.Subscript.Tag = SUBSCRIPT_PROPERTY_T;
		self->Kind.Subscript.Kind.Property = prop;
		self->Kind.Subscript.Index = temp;
	}
	if(receiver_gtype != NULL) {
		self->Tag = BOUND_INVOKE_SUBSCRIPT_T;
		self->Kind.Subscript.Operator = bc_ArgFindOperatorOverloadClass(BC_TYPE2CLASS(bc_GENERIC2TYPE(receiver_gtype)), OPERATOR_SUB_SCRIPT_GET_T, self->Arguments, env, cctx, &temp);
		self->Index = temp;
		if(temp == -1) {
			bc_Panic(BCERROR_INVOKE_BOUND_UNDEFINED_METHOD_T,
				bc_Ref2Str(self->Name)
			);
		}
	}
	if(self->Index == -1) {
		bc_Panic(BCERROR_INVOKE_BOUND_UNDEFINED_METHOD_T,
			bc_Ref2Str(bc_GetTypeName(ctype)),
			bc_Ref2Str(self->Name)
		);
	}
	bc_PopCallContext(cctx);
}

static void ILInvokeBound_args_delete(bc_VectorItem item) {
	bc_ILArgument* e = (bc_ILArgument*)item;
	bc_DeleteILArgument(e);
}

static void GenerateILInvokeBound_method(bc_ILInvokeBound* self, bc_Enviroment* env, bc_CallContext* cctx) {
	assert(self->Tag != BOUND_INVOKE_UNDEFINED_T);
	if(self->Tag != BOUND_INVOKE_METHOD_T) {
		return;
	}
	for(int i=0; i<self->TypeArgs->Length; i++) {
		bc_ILTypeArgument* e = (bc_ILTypeArgument*)bc_AtVector(self->TypeArgs, i);
		assert(e->GType != NULL);
		bc_AddOpcodeBuf(env->Bytecode, OP_GENERIC_ADD);
		bc_GenerateGenericType(e->GType, env);
	}
	for(int i=0; i<self->Arguments->Length; i++) {
		bc_ILArgument* e = (bc_ILArgument*)bc_AtVector(self->Arguments, i);
		bc_GenerateILFactor(e->Factor, env, cctx);
		if(bc_GetLastPanic()) {
			return;
		}
	}
	if(bc_IsStaticModifier(self->Kind.Method->Modifier)) {
		bc_AddOpcodeBuf(env->Bytecode, (bc_VectorItem)OP_INVOKESTATIC);
		bc_AddOpcodeBuf(env->Bytecode, (bc_VectorItem)self->Kind.Method->Parent->AbsoluteIndex);
		bc_AddOpcodeBuf(env->Bytecode,(bc_VectorItem) self->Index);
	} else {
		bc_AddOpcodeBuf(env->Bytecode,(bc_VectorItem) OP_THIS);
		if(self->Kind.Method->Access == ACCESS_PRIVATE_T) {
			bc_AddOpcodeBuf(env->Bytecode, (bc_VectorItem)OP_INVOKESPECIAL);
			bc_AddOpcodeBuf(env->Bytecode, (bc_VectorItem)self->Index);
		} else {
			bc_AddOpcodeBuf(env->Bytecode, (bc_VectorItem)OP_INVOKEVIRTUAL);
			bc_AddOpcodeBuf(env->Bytecode, (bc_VectorItem)self->Index);
		}
	}
}

static void GenerateILInvokeBound_subscript(bc_ILInvokeBound* self, bc_Enviroment* env, bc_CallContext* cctx) {
	assert(self->Tag != BOUND_INVOKE_UNDEFINED_T);
	if(self->Tag != BOUND_INVOKE_SUBSCRIPT_T) {
		return;
	}
	for(int i=0; i<self->TypeArgs->Length; i++) {
		bc_ILTypeArgument* e = (bc_ILTypeArgument*)bc_AtVector(self->TypeArgs, i);
		assert(e->GType != NULL);
		bc_AddOpcodeBuf(env->Bytecode, OP_GENERIC_ADD);
		bc_GenerateGenericType(e->GType, env);
	}
	for(int i=0; i<self->Arguments->Length; i++) {
		bc_ILArgument* e = (bc_ILArgument*)bc_AtVector(self->Arguments, i);
		bc_GenerateILFactor(e->Factor, env, cctx);
		if(bc_GetLastPanic()) {
			return;
		}
	}
	bc_SubscriptDescriptor subs = self->Kind.Subscript;
	if(subs.Tag == SUBSCRIPT_LOCAL_T) {
		bc_AddOpcodeBuf(env->Bytecode, OP_LOAD);
		bc_AddOpcodeBuf(env->Bytecode, subs.Index);
	} else if(subs.Tag == SUBSCRIPT_FIELD_T) {
		bc_AddOpcodeBuf(env->Bytecode, OP_THIS);
		bc_GenerateGetField(env->Bytecode, subs.Kind.Field, subs.Index);
	} else if(subs.Tag == SUBSCRIPT_PROPERTY_T) {
		bc_AddOpcodeBuf(env->Bytecode, OP_THIS);
		bc_GenerateGetProperty(env->Bytecode, subs.Kind.Property, subs.Index);
	} else {
		assert(false);
	}
	bc_AddOpcodeBuf(env->Bytecode, OP_INVOKEOPERATOR);
	bc_AddOpcodeBuf(env->Bytecode, self->Index);
}

static bc_GenericType* ILInvokeBound_return_gtype(bc_ILInvokeBound* self, bc_CallContext* cctx) {
	assert(self->Tag != BOUND_INVOKE_UNDEFINED_T);
	return bc_ApplyGenericType(self->Tag == BOUND_INVOKE_METHOD_T ?
			self->Kind.Method->ReturnGType :
			self->Kind.Subscript.Operator->ReturnGType, cctx);
}

static bc_GenericType* EvalILInvokeBoundImpl(bc_ILInvokeBound * self, bc_Enviroment * env, bc_CallContext* cctx) {
	bc_Type* tp = NULL;
	//メソッドが見つからない
	ILInvokeBound_check(self, env, cctx);
	if(bc_GetLastPanic()) {
		return NULL;
	}
	bc_CallFrame* cfr = NULL;
	if(self->Tag == BOUND_INVOKE_METHOD_T) {
		cfr = bc_PushCallContext(cctx, FRAME_SELF_INVOKE_T);
		cfr->Kind.SelfInvoke.Args = self->Arguments;
		cfr->Kind.SelfInvoke.TypeArgs = self->TypeArgs;
	} else {
		cfr = bc_PushCallContext(cctx, FRAME_INSTANCE_INVOKE_T);
		cfr->Kind.InstanceInvoke.Receiver = bc_ApplyGenericType(bc_GetSubscriptReceiver(&self->Kind.Subscript), cctx);
		cfr->Kind.InstanceInvoke.Args = self->Arguments;
		cfr->Kind.InstanceInvoke.TypeArgs = self->TypeArgs;
	}

	if(ILInvokeBound_return_gtype(self, cctx)->Tag != GENERIC_TYPE_TAG_NONE_T) {
		resolve_non_default(self, env, cctx);
		assert(self->Resolved != NULL);
		bc_PopCallContext(cctx);
		return self->Resolved;
	} else {
		resolve_default(self, env, cctx);
		assert(self->Resolved != NULL);
		bc_PopCallContext(cctx);
		return self->Resolved;
	}
	bc_PopCallContext(cctx);
	assert(self->Resolved != NULL);
	return self->Resolved;
}