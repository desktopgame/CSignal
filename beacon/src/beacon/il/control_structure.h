#ifndef BEACON_IL_CONTROL_STRUCTURE_H
#define BEACON_IL_CONTROL_STRUCTURE_H
#include "../util/vector.h"

typedef struct control_structure {
	vector* while_start;
	vector* while_end;
} control_structure;

void control_structure_alloc(control_structure* self);

void control_structure_free(control_structure self);
#endif