#include "modifier_type.h"
#include <stdio.h>

modifier_type modifier_static_native() {
	return modifier_static | modifier_native;
}

bool modifier_is_static(modifier_type type) {
	return (type & modifier_static);
}

bool modifier_is_native(modifier_type type) {
	return (type & modifier_native);
}

void modifier_print(modifier_type type) {
	if (type == (modifier_static | modifier_native)) {
		printf("static native");
		return;
	}
	switch (type) {
		case modifier_none:
			printf("none");
			break;

		case modifier_static:
			printf("static");
			break;

		case modifier_native:
			printf("native");
			break;

		default:
			break;
	}
}
