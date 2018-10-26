#include "class_loader_ilload_type_module_impl.h"
#include "class_loader_ilload_factor_module_impl.h"
#include "class_loader_ilload_stmt_module_impl.h"
#include "../../ast/ast.h"
#include "../../env/fqcn_cache.h"
#include "../../env/generic_cache.h"
#include "../../util/text.h"

#include "../class_loader.h"
//#include "../../il/ILTypeParameter_rule.h"
#include "../../il/il_type_parameter.h"
#include "../../il/il_type_argument.h"
#include "../../il/il_parameter.h"
#include "../../il/il_argument.h"
#include "class_loader_ilload_impl.h"
#include <assert.h>

//proto
static void CLILFQCNCache_impl(AST* afqcn, FQCNCache* fqcn, int level);
static void CLILGenericCache_impl(AST* afqcn, GenericCache* dest);
static void CLILGenericCache_inner(AST* atype_args, GenericCache* dest);
static void CLILTypeParameter_rule(struct ClassLoader* self, struct AST* asource, Vector* dest);
static void ast_fqcn_flatten(AST* afqcn, Vector* dest);
static void CLILArgumentListImpl(ClassLoader* self, Vector* list, AST* asource);

void CLILFQCNCache(AST* afqcn, FQCNCache* fqcn) {
	CLILFQCNCache_impl(afqcn, fqcn, 0);
}

void CLILGenericCache(AST* afqcn, GenericCache* dest) {
	if(afqcn->Tag == AST_FQCN_CLASS_NAME_T) {
		dest->FQCN->Name = afqcn->Attr.StringVValue;
		return;
	}
	CLILGenericCache_impl(afqcn, dest);
	FQCNCache* body = dest->FQCN;
	//FIXME: Int のような文字パースで失敗してしまうので対策
	if (body->Name == 0 &&
		body->Scope->Length > 0) {
		body->Name = (StringView)PopVector(body->Scope);
	}
}

void CLILTypenameList(ClassLoader * self, Vector * dst, AST* atypename_list) {
	if (IsBlankAST(atypename_list)) {
		return;
	}
	if (atypename_list->Tag == AST_TYPENAME_T) {
		GenericCache* e = NewGenericCache();
		//[typename [fqcn]]
		CLILGenericCache(atypename_list, e);
		PushVector(dst, e);
	} else if(atypename_list->Tag == AST_TYPENAME_LIST_T) {
		for (int i = 0; i < atypename_list->Children->Length; i++) {
			CLILTypenameList(self, dst, AtAST(atypename_list, i));
		}
	}
}


void CLILTypeParameter(ClassLoader* self, AST* asource, Vector* dest) {
	if (IsBlankAST(asource)) {
		return;
	}
	if (asource->Tag == AST_TYPE_PARAMETER_LIST_T) {
		for (int i = 0; i < asource->Children->Length; i++) {
			CLILTypeParameter(self, AtAST(asource, i), dest);
		}
		return;
	}
	assert(asource->Tag == AST_TYPE_PARAMETER_T ||
		   asource->Tag == AST_TYPE_IN_PARAMETER_T ||
		   asource->Tag == AST_TYPE_OUT_PARAMETER_T);
	AST* arule_list = FirstAST(asource);
	ILTypeParameter* iltypeparam = NewILTypeParameter(asource->Attr.StringVValue);
	if (asource->Tag == AST_TYPE_IN_PARAMETER_T) iltypeparam->Tag = IL_TYPE_PARAMETER_KIND_IN_T;
	if (asource->Tag == AST_TYPE_OUT_PARAMETER_T) iltypeparam->Tag = IL_TYPE_PARAMETER_KIND_OUT_T;
	PushVector(dest, iltypeparam);
	//制約があるならそれも設定
	//制約はとりあえずなしで
	assert(IsBlankAST(arule_list));
}

void CLILTypeArgument(ClassLoader* self, AST* atype_args, Vector* dest) {
	if(IsBlankAST(atype_args)) {
		return;
	}
	if(atype_args->Tag == AST_TYPENAME_LIST_T) {
		for(int i=0; i<atype_args->Children->Length; i++) {
			AST* e = AtAST(atype_args, i);
			CLILTypeArgument(self, e, dest);
		}
	} else if(atype_args->Tag == AST_TYPENAME_T) {
		ILTypeArgument* iltype_arg = NewILTypeArgument();
		PushVector(dest, iltype_arg);
		CLILGenericCache(atype_args, iltype_arg->GCache);
	} else assert(false);
}

void CLILParameterList(ClassLoader* self, Vector* list, AST* asource) {
	if (asource->Tag == AST_PARAMETER_LIST_T) {
		for (int i = 0; i < asource->Children->Length; i++) {
			CLILParameterList(self, list, AtAST(asource, i));
		}
	} else if (asource->Tag == AST_PARAMETER_T) {
		AST* aGetTypeName = FirstAST(asource);
		AST* aaccess_name = SecondAST(asource);
		ILParameter* p = NewILParameter(aaccess_name->Attr.StringVValue);
		CLILGenericCache(aGetTypeName, p->GCache);
		PushVector(list, p);
	}
}

void CLILArgumentList(ClassLoader* self, Vector* list, AST* asource) {
	CLILArgumentListImpl(self, list, asource);
}
//private
static void CLILFQCNCache_impl(AST* afqcn, FQCNCache* fqcn, int level) {
	Vector* v = NewVector();
	ast_fqcn_flatten(afqcn, v);
	for(int i=0; i<v->Length; i++) {
		StringView S = (StringView)AtVector(v, i);
		if(i < v->Length - 1) {
			PushVector(fqcn->Scope, S);
		} else {
			fqcn->Name = S;
		}
	}
	DeleteVector(v, VectorDeleterOfNull);
}

static void CLILGenericCache_impl(AST* afqcn, GenericCache* dest) {
	FQCNCache* body = dest->FQCN;
	//型引数を解析する
	if (afqcn->Tag == AST_TYPENAME_T) {
		AST* atype_args = SecondAST(afqcn);
		if (!IsBlankAST(atype_args)) {
			CLILGenericCache_inner(atype_args, dest);
		}
	}
	if (afqcn->Tag == AST_TYPENAME_T) {
		CLILGenericCache_impl(FirstAST(afqcn), dest);
		return;
	}
	if (afqcn->Tag == AST_FQCN_T ||
		afqcn->Tag == AST_FQCN_PART_LIST_T) {
		if (afqcn->Tag == AST_FQCN_PART_LIST_T &&
			afqcn->Children->Length == 0) {
			//FIXME:もうちょっと高速に出来る
			//FIXME:とりあえずここでタグを直してるけどast.cの時点でどうにかするべき
			afqcn->Tag = AST_FQCN_CLASS_NAME_T;
			body->Name = afqcn->Attr.StringVValue;
			return;
		}
		for (int i = 0; i < afqcn->Children->Length; i++) {
			AST* c = AtAST(afqcn, i);
			CLILGenericCache_impl(c, dest);
		}
	} else {
		//FIXME:とりあえずここでタグを直してるけどast.cの時点でどうにかするべき
		PushVector(body->Scope, afqcn->Attr.StringVValue);
		afqcn->Tag = AST_FQCN_PART_T;
	}
}

static void CLILGenericCache_inner(AST* atype_args, GenericCache* dest) {
	if (atype_args->Tag == AST_TYPENAME_LIST_T) {
		for (int i = 0; i < atype_args->Children->Length; i++) {
			AST* e = AtAST(atype_args, i);
			CLILGenericCache_inner(e, dest);
		}
	} else {
		GenericCache* newCache = NewGenericCache();
		CLILGenericCache(atype_args, newCache);
		PushVector(dest->TypeArgs, newCache);
	}
}

static void CLILTypeParameter_rule(ClassLoader* self, AST* asource, Vector* dest) {
	assert(false);
	/*
	if (source->Tag == AST_TYPE_PARAMETER_LIST_T) {
		for (int i = 0; i < source->child_count; i++) {
			CLILTypeParameter_rule(self, AtAST(source, i), dest);
		}
	} else {
		if (source->Tag == AST_TYPENAME_T) {
			ILTypeParameter_rule* rule = ILTypeParameter_rule_new();
			rule->Tag = ILTypeParameter_rule_polymorphic;
			rule->u.fqcn_ = NewGenericCache();
			CLILGenericCache(source, rule->u.fqcn_);
			PushVector(dest, rule);
		}
	}
	*/
}

static void ast_fqcn_flatten(AST* afqcn, Vector* dest) {
	if(afqcn->Tag == AST_FQCN_PART_T) {
		PushVector(dest, afqcn->Attr.StringVValue);
	} else {
		for(int i=0; i<afqcn->Children->Length; i++) {
			ast_fqcn_flatten(AtAST(afqcn, i), dest);
		}
	}
}

static void CLILArgumentListImpl(ClassLoader* self, Vector* list, AST* asource) {
	if (asource->Tag == AST_ARGUMENT_LIST_T) {
		for (int i = 0; i < asource->Children->Length; i++) {
			CLILArgumentListImpl(self, list, AtAST(asource, i));
		}
	} else if (asource->Tag == AST_ARGUMENT_T) {
		AST* aprimary = FirstAST(asource);
		ILArgument* ilarg = NewILArgument();
		ilarg->Factor = CLILFactor(self, aprimary);
		PushVector(list, ilarg);
	}
}