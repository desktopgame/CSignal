#ifndef BEACON_IL_CONTROL_STRUCTURE_H
#define BEACON_IL_CONTROL_STRUCTURE_H
#include "../util/vector.h"

typedef struct ControlStructure {
	Vector* WhileStartTable;
	Vector* WhileEndTable;
} ControlStructure;

void AllocControlStructure(ControlStructure* self);

void FreeControlStructure(ControlStructure self);
#endif