#include "interface_impl.h"
//#include "../type_interface.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../../env/method.h"
#include "../../env/generic_type.h"
#include "../../env/property.h"
#include "../../env/parameter.h"
#include "meta_impl.h"
#include "../generic_type.h"
#include "../type_parameter.h"
#include <stdio.h>
//proto
Vector* GetGenericInterfaceTreeInterfaceImpl(interface_* self);
static void DeleteInterface_method(VectorItem item);
static void interface_DeleteTypeParameter(VectorItem item);
static void interface_GenericType_list_delete(VectorItem item);
static void FlattenMethodInterfaceImpl(interface_* self, Vector* dest, int depth);
static void DeleteInterface_Property(VectorItem item);

Type* WrapInterface(interface_ * self) {
	Type* ret = NewType();
	ret->Tag = TYPE_INTERFACE_T;
	ret->Kind.Interface = self;
	self->parent = ret;
	return ret;
}

interface_ * NewInterface(StringView namev) {
	interface_* ret = (interface_*)MEM_MALLOC(sizeof(interface_));
	ret->namev = namev;
	ret->impl_list = NewVector();
	ret->location = NULL;
	ret->method_list = NewVector();
	ret->prop_list = NewVector();
	ret->vt = NULL;
	ret->GetParameterListType = NewVector();
	ret->parent = NULL;
	return ret;
}

void AddMethodInterface(interface_ * self, Method * m) {
	PushVector(self->method_list, m);
}

void AddPropertyInterface(interface_* self, Property* p) {
	PushVector(self->prop_list, p);
}

Method * ILFindMethodInterface(interface_ * self, StringView namev, Vector * args, Enviroment * env, CallContext* cctx, int * outIndex) {
	return MetaILFindMethod(self->method_list, namev, args, env,cctx, outIndex);
}

Method* GFindMethodInterface(interface_* self, StringView namev, Vector* gargs, int* outIndex) {
	return MetaGFindMethod(self->method_list, namev, gargs, outIndex);
}

Vector* FlattenMethodInterfaceList(Vector* inter_list) {
	Vector* ret = NewVector();
	for(int i=0; i<inter_list->Length; i++) {
		interface_* inter = AtVector(inter_list, i);
		//インターフェイスのメソッド一覧を挿入
		Vector* list = FlattenMethodInterface(inter);
		for(int j=0; j<list->Length; j++) {
			PushVector(ret, AtVector(list, j));
		}
		DeleteVector(list, VectorDeleterOfNull);
	}
	return ret;
}

Vector* FlattenMethodInterface(interface_* self) {
	Vector* ret = NewVector();
	FlattenMethodInterfaceImpl(self, ret, 0);
	return ret;
}

void CreateVTableInterface(interface_ * self) {
	//初期化済み
	if (self->vt != NULL) {
		return;
	}
	self->vt = NewVTable();
	//他のインターフェイスを継承していないならフラットに並べる
	if (self->impl_list->Length == 0) {
		for (int i = 0; i < self->method_list->Length; i++) {
			AddVTable(self->vt, AtVector(self->method_list, i));
		}
	} else {
		for (int i = 0; i < self->impl_list->Length; i++) {
			GenericType* ginter = (GenericType*)AtVector(self->impl_list, i);
			Type* cinter = GENERIC2TYPE(ginter);
			interface_* inter = TYPE2INTERFACE(cinter);
//			interface_* inter = (interface_*)AtVector(self->impl_list, i);
			CreateVTableInterface(inter);
			CopyVTable(inter->vt, self->vt);
		}
		for (int i = 0; i < self->method_list->Length; i++) {
			AddVTable(self->vt, AtVector(self->method_list, i));
		}
	}
}

void UnlinkInterface(interface_ * self) {
	DeleteVector(self->method_list, DeleteInterface_method);
	DeleteVector(self->prop_list, DeleteInterface_Property);
	DeleteVector(self->impl_list, VectorDeleterOfNull);
	DeleteVTable(self->vt);
}

void DeleteInterface(interface_ * self) {
	DeleteVector(self->GetParameterListType, interface_DeleteTypeParameter);
	MEM_FREE(self);
}

GenericType* IsContainsTypeInterface(GenericType* source, interface_* find) {
	interface_* self = source->CoreType->Kind.Interface;
	if(self == find) {
		return source;
	}
	for(int i=0; i<self->impl_list->Length; i++) {
		GenericType* gE = AtVector(self->impl_list, i);
		if(gE->CoreType->Kind.Interface == find) {
			return gE;
		}
	}
	return NULL;
}

bool IsFunctionalInterface(interface_* self) {
	return GetFunctionInterface(self) != NULL;
}

Method* GetFunctionInterface(interface_* self) {
	Vector* v = FlattenMethodInterface(self);
	Method* ret = NULL;
	if(v->Length == 1) {
		ret = AtVector(v, 0);
	}
	DeleteVector(v, VectorDeleterOfNull);
	return ret;
}


Vector* GetGenericInterfaceTreeInterface(interface_* self) {
	return GetGenericInterfaceTreeInterfaceImpl(self);
}

GenericType* FindInterfaceInterface(interface_* self, Type* tinter) {
	assert(tinter->Tag == TYPE_INTERFACE_T);
	if (self == TYPE2INTERFACE(tinter)) {
		return NULL;
	}
	for (int i = 0; i < self->impl_list->Length; i++) {
		GenericType* e = AtVector(self->impl_list, i);
		if (e->CoreType == tinter) {
			return e;
		}
	}
	return NULL;
}

//private
Vector* GetGenericInterfaceTreeInterfaceImpl(interface_* self) {
	Vector* ret = NewVector();
	for(int i=0; i<self->impl_list->Length; i++) {
		GenericType* ginter = AtVector(self->impl_list, i);
		PushVector(ret, ginter);
		Vector* inner = GetGenericInterfaceTreeInterfaceImpl(TYPE2INTERFACE(GENERIC2TYPE(ginter)));
		MergeVector(ret, inner);
		DeleteVector(inner, VectorDeleterOfNull);
	}
	return ret;
}
static void DeleteInterface_method(VectorItem item) {
	Method* e = (Method*)item;
	DeleteMethod(e);
}

static void interface_DeleteTypeParameter(VectorItem item) {
	TypeParameter* e = (TypeParameter*)item;
	DeleteTypeParameter(e);
}

static void interface_GenericType_list_delete(VectorItem item) {
	//GenericType* e = (GenericType*)item;
	//generic_DeleteType(e);
}

static void FlattenMethodInterfaceImpl(interface_* self, Vector* dest, int depth) {
	//tekitou
	#if defined(DEBUG)
	const char* intername = Ref2Str(self->namev);
	#endif
	assert(depth < 42);
	for(int i=0; i<self->method_list->Length; i++) {
		Method* m = AtVector(self->method_list, i);
		PushVector(dest, m);
	}
	for(int i=0; i<self->impl_list->Length; i++) {
		GenericType* e = AtVector(self->impl_list, i);
		interface_* inter = TYPE2INTERFACE(e->CoreType);
		FlattenMethodInterfaceImpl(inter, dest, depth + 1);
	}
}

static void DeleteInterface_Property(VectorItem item) {
	Property* e = (Property*)item;
	DeleteProperty(e);
}