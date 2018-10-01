#include "namespace.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "type_interface.h"
#include "TYPE_IMPL.h"
#include "script_context.h"
#include "../lib/bc_library_interface.h"
#include "../util/text.h"
#include "../util/mem.h"

//static tree_map* tree_map_root = NULL;
//proto
static namespace_* namespace_malloc(string_view namev);

static void UnlinkNamespace_namespace(NumericMapKey key, NumericMapItem item);
static void DeleteNamespace_namespace(NumericMapKey key, NumericMapItem item);

static void UnlinkNamespace_type(NumericMapKey key, NumericMapItem item);
static void DeleteNamespace_type(NumericMapKey key, NumericMapItem item);

static void namespace_dump_root(NumericMap* root, bool callSelf, int depth);
static void namespace_dump_impl(namespace_* root, int depth);
static void namespace_put_indent(int depth);
static void namespace_dump_class(NumericMap* root, bool isRoot, int depth);

namespace_ * CreateNamespaceAtRoot(string_view namev) {
	script_context* ctx = GetCurrentScriptContext();
	if (ctx->namespace_nmap == NULL) {
		ctx->namespace_nmap = NewNumericMap();
	}
	tree_item item = GetNumericMapValue(ctx->namespace_nmap, namev);
	if (item == NULL) {
		namespace_* newNamespace = namespace_malloc(namev);
		PutNumericMap(ctx->namespace_nmap, namev, newNamespace);
		return newNamespace;
	} else return (namespace_*)item;
}

namespace_ * FindNamespaceFromRoot(string_view namev) {
	script_context* ctx = GetCurrentScriptContext();
	return CFindNamespaceFromRoot(ctx, namev);
}

namespace_* CFindNamespaceFromRoot(script_context* sctx, string_view namev) {
	if (sctx->namespace_nmap == NULL) {
		return NULL;
	}
	return (namespace_*)GetNumericMapValue(sctx->namespace_nmap, namev);
}

namespace_ * AddNamespaceNamespace(namespace_ * self, string_view namev) {
	assert(self != NULL);
	namespace_* child = FindNamespaceFromNamespace(self, namev);
	if (child == NULL) {
		namespace_* newNamespace = namespace_malloc(namev);
		newNamespace->parent = self;
		child = newNamespace;
		PutNumericMap(self->namespace_map, namev, child);
		//PushVector(self->namespace_vec, child);
		self->ref_count++;
	}
	return child;
}

struct type* AddTypeNamespace(namespace_* self, type* type) {
	script_context* ctx = GetCurrentScriptContext();
	type->location = self;
	PutNumericMap(self->type_map, type_name(type), type);
	type->absolute_index = ctx->type_vec->length;
	PushVector(ctx->type_vec, type);
	return type;
}

namespace_ * FindNamespaceFromNamespace(namespace_ * self, string_view namev) {
	assert(self != NULL);
	return GetNumericMapValue(self->namespace_map, namev);
}

type * FindTypeFromNamespace(namespace_ * self, string_view namev) {
	assert(self != NULL);
	return GetNumericMapValue(self->type_map, namev);
}

class_ * FindClassFromNamespace(namespace_ * self, string_view namev) {
	return type_as_class(FindTypeFromNamespace(self, namev));
}

interface_ * FindInterfaceFromNamespace(namespace_ * self, string_view namev) {
	return type_as_interface(FindTypeFromNamespace(self, namev));
}

namespace_ * GetBeaconNamespace() {
	return FindNamespaceFromRoot(InternString("beacon"));
}

namespace_ * GetLangNamespace() {
	return FindNamespaceFromNamespace(GetBeaconNamespace(), InternString("lang"));
}

namespace_* GetUnsafeNamespace() {
	return FindNamespaceFromNamespace(GetBeaconNamespace(), InternString("unsafe"));
}

namespace_* GetPlaceholderNamespace() {
	return FindNamespaceFromRoot(InternString("$placeholder"));
}

type * GetObjectTypeNamespace() {
	return bc_object_type();
}

type * GetIntTypeNamespace() {
	return bc_int_type();
}

type * GetDoubleTypeNamespace() {
	return bc_double_type();
}

type * GetCharTypeNamespace() {
	return bc_char_type();
}

type * GetStringTypeNamespace() {
	return bc_string_type();
}

type * GetBoolTypeNamespace() {
	return bc_bool_type();
}

type * GetVoidTypeNamespace() {
	return bc_void_type();
}

type * GetNullTypeNamespace() {
	return bc_null_type();
}

type* GetExceptionTypeNamespace() {
	return bc_exception_type();
}

void UnlinkNamespace(namespace_ * self) {
	EachNumericMap(self->namespace_map, UnlinkNamespace_namespace);
	EachNumericMap(self->type_map, UnlinkNamespace_type);
}

string_view NamespaceToString(namespace_* self) {
	if(self->parent == NULL) {
		return self->namev;
	}
	return ConcatIntern(
		Ref2Str(ConcatIntern(
			Ref2Str(NamespaceToString(self->parent)),
			InternString("::")
		)),
		self->namev
	);
}

void DeleteNamespace(namespace_ * self) {
	DeleteNumericMap(self->namespace_map, DeleteNamespace_namespace);
	DeleteNumericMap(self->type_map, DeleteNamespace_type);
	MEM_FREE(self);
}

//private
static namespace_* namespace_malloc(string_view namev) {
	namespace_* ret = (namespace_*)MEM_MALLOC(sizeof(namespace_));
	ret->namespace_map = NewNumericMap();
	ret->type_map = NewNumericMap();
	ret->parent = NULL;
	ret->namev = namev;
	ret->ref_count = 0;
	return ret;
}

static void UnlinkNamespace_namespace(NumericMapKey key, NumericMapItem item) {
	namespace_* e = (namespace_*)item;
	UnlinkNamespace(e);
}

static void DeleteNamespace_namespace(NumericMapKey key, NumericMapItem item) {
	namespace_* e = (namespace_*)item;
	DeleteNamespace(e);
}

static void UnlinkNamespace_type(NumericMapKey key, NumericMapItem item) {
	type* e = (type*)item;
	type_unlink(e);
}

static void DeleteNamespace_type(NumericMapKey key, NumericMapItem item) {
	type* e = (type*)item;
	type_delete(e);
}

static void namespace_dump_root(NumericMap* root, bool callSelf, int depth) {
	if (root == NULL) {
		return;
	}
	if (callSelf) {
		namespace_dump_impl((namespace_*)root->item, depth);
	}
	if (root->left != NULL) {
		namespace_dump_root(root->left, true, depth);
	}
	if (root->right != NULL) {
		namespace_dump_root(root->right, true, depth);
	}
}

static void namespace_dump_impl(namespace_* root, int depth) {
	namespace_put_indent(depth);
	printf("%s", Ref2Str(root->namev));
	Println();
	namespace_dump_class(root->type_map, true, depth + 1);
	namespace_dump_root(root->namespace_map, false, depth + 1);
}

static void namespace_put_indent(int depth) {
	for (int i = 0; i < depth; i++) {
		printf("    ");
	}
}

static void namespace_dump_class(NumericMap* root, bool isRoot, int depth) {
	if (!isRoot && (root == NULL || root->item == NULL)) {
		return;
	}
	if (!isRoot) {
		type* e = ((type*)root->item);
		//type_dump(e, depth);
		assert(false);
	}
	namespace_dump_class(root->left, false, depth);
	namespace_dump_class(root->right, false, depth);
}