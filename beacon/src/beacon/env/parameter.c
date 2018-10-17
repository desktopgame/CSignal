#include "parameter.h"
#include <stdlib.h>
#include "../util/text.h"
#include "../util/mem.h"
#include "../env/generic_type.h"

parameter * NewParameter(StringView namev) {
	parameter* ret = (parameter*)MEM_MALLOC(sizeof(parameter));
	ret->namev = namev;
	ret->gtype = NULL;
	return ret;
}

void DeleteParameter(parameter * self) {
	MEM_FREE(self);
}

bool IsOverwrappedParameterName(Vector* parameters, StringView* namev) {
	for(int i=0; i<parameters->Length; i++) {
		parameter* e = (parameter*)AtVector(parameters, i);
		for(int j=0; j<parameters->Length; j++) {
			if(i == j) { continue; }
			parameter* e2 = (parameter*)AtVector(parameters, j);
			if(e->namev == e2->namev) {
				(*namev) = e->namev;
				return true;
			}
		}
	}
	return false;
}