#include "il_error.h"
#include <stdio.h>
#include <assert.h>
#include "../util/vector.h"
#include "../util/mem.h"
#include "../util/test/xtest.h"

//proto
static void il_error_print(FILE* fp, il_error_id error_id, va_list ap);
static vector* gPanicStateVec = NULL;

typedef struct panic_state {
	bool panic;
} panic_state;


void il_error_report(il_error_id error_id, ...) {
	va_list ap;
	va_start(ap, error_id);
	il_error_vreport(error_id, ap);
	va_end(ap);
}

void il_error_vreport(il_error_id error_id, va_list ap) {
	il_error_print(stdout, error_id, ap);
	assert(gPanicStateVec != NULL);
	assert(gPanicStateVec->length > 0);
	panic_state* ps = (panic_state*)vector_top(gPanicStateVec);
	ps->panic = true;
}

void il_error_enter() {
	if(gPanicStateVec == NULL) {
		gPanicStateVec = vector_new();
	}
	panic_state* ps = (panic_state*)MEM_MALLOC(sizeof(panic_state));
	ps->panic = false;
	vector_push(gPanicStateVec, ps);
}

void il_error_exit() {
	assert(gPanicStateVec != NULL);
	assert(gPanicStateVec->length > 0);
	panic_state* ps = (panic_state*)vector_pop(gPanicStateVec);
	MEM_FREE(ps);
	if(gPanicStateVec->length == 0) {
		vector_delete(gPanicStateVec, vector_deleter_null);
		gPanicStateVec = NULL;
	}
}

void il_error_clear() {
	assert(gPanicStateVec->length > 0);
	panic_state* ps = (panic_state*)vector_top(gPanicStateVec);
	ps->panic = false;
}

bool il_error_panic() {
	assert(gPanicStateVec->length > 0);
	panic_state* ps = (panic_state*)vector_top(gPanicStateVec);
	return ps->panic;
}
//private
static void il_error_print(FILE* fp, il_error_id error_id, va_list ap) {
	char* fmt = NULL;
	switch(error_id) {
		case ilerror_undefined_class:
			fmt = "undefined class: %s";
			break;
		case ilerror_undefined_variable:
			fmt = "undefined variable: %s";
			break;
		case ilerror_undefined_method:
			fmt = "undefined method: %s";
			break;
		case ilerror_undefined_field:
			fmt = "undefined field: %s";
			break;
		case ilerror_undefined_ctor:
			fmt = "undefined ctor: %s";
			break;
		default:
			fmt = "if shown this message, it compiler bug";
			break;
	}
	if(xtest_now()) {
		xtest_vprintf(fmt, ap);
		xtest_printf("\n");
	} else {
		vfprintf(fp, fmt, ap);
		fprintf(fp, "\n");
	}
}