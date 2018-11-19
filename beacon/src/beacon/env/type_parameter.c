#include "type_parameter.h"
#include "../util/mem.h"
#include "../util/text.h"
#include "../util/vector.h"
#include "../il/il_type_parameter.h"
#include <assert.h>

//proto
static void delete_rule(VectorItem item);

bc_TypeParameter * bc_NewTypeParameter(StringView name) {
	bc_TypeParameter* ret = (bc_TypeParameter*)MEM_MALLOC(sizeof(bc_TypeParameter));
	ret->Name = name;
	ret->Kind = TYPE_PARAMETER_KIND_DEFAULT_T;
	return ret;
}

bc_TypeParameter * bc_DupTypeParameter(ILTypeParameter * src) {
	bc_TypeParameter* ret = bc_NewTypeParameter(src->Name);
	switch (src->Tag) {
		case IL_TYPE_PARAMETER_KIND_DEFAULT_T:
			ret->Kind = TYPE_PARAMETER_KIND_DEFAULT_T;
			break;
		case IL_TYPE_PARAMETER_KIND_IN_T:
			ret->Kind = TYPE_PARAMETER_KIND_IN_T;
			break;
		case IL_TYPE_PARAMETER_KIND_OUT_T:
			ret->Kind = TYPE_PARAMETER_KIND_OUT_T;
			break;
		default:
			break;
	}
//	TypeParameter_rule_list_dup(src->rule_vec, ret->rule_vec, cache);
	return ret;
}

void bc_DupTypeParameterList(Vector* ilSource, Vector* sgDest) {
	assert(ilSource != NULL);
	//これはILレベルの<K, V>の並びを
	//SGレベルの<K, V> へ変換します。
	//<K(IComparable<K>), V>のような宣言をするとき、
	//Kは仮想型としてIComparableで正しく認識されます。
	//そのためには、TypeParameterをとりえず登録しておいて、
	//あとからルール一覧を対応づける必要があります。
	//DupTypeParameterからルールの複製を削除したのもそのためです。
	for (int i = 0; i < ilSource->Length; i++) {
		ILTypeParameter* e = (ILTypeParameter*)AtVector(ilSource, i);
		bc_TypeParameter* newTP = bc_DupTypeParameter(e);
		PushVector(sgDest, newTP);
		//TypeParameter_rule_list_dup(e->rule_vec, newTP->rule_vec, cache);
	}
}

void bc_PrintTypeParameter(Vector* v) {
	//FIXME:il_TypeParameterからのコピペ
	if (v->Length <= 0) {
		return;
	}
	printf("[");
	for (int i = 0; i < v->Length; i++) {
		bc_TypeParameter* e = (bc_TypeParameter*)AtVector(v, i);
		if (e->Kind == TYPE_PARAMETER_KIND_IN_T) {
			printf("in ");
		} else if (e->Kind == TYPE_PARAMETER_KIND_OUT_T) {
			printf("out ");
		}
		printf("%s", Ref2Str(e->Name));
		if (i != v->Length - 1) {
			printf(", ");
		}
	}
	printf("]");
}

void bc_DeleteTypeParameter(bc_TypeParameter * self) {
	MEM_FREE(self);
}

bool bc_IsOverwrappedTypeParameterName(Vector* tparameters, StringView* namev) {
	if(tparameters->Length <= 1) {
		return false;
	}
	for(int i=0; i<tparameters->Length; i++) {
		bc_TypeParameter* e = (bc_TypeParameter*)AtVector(tparameters, i);
		for(int j=0; j<tparameters->Length; j++) {
			if(i == j) { continue; }
			bc_TypeParameter* e2 = (bc_TypeParameter*)AtVector(tparameters, j);
			if(e->Name == e2->Name) {
				(*namev) = e->Name;
				return true;
			}
		}
	}
	return false;
}

//private
static void delete_rule(VectorItem item) {
//	TypeParameter_rule* e = (TypeParameter_rule*)item;
//	TypeParameter_rule_delete(e);
}

