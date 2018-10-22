#ifndef BEACON_IL_FACTOR_INVOKE_SUBSCRIPT_DESCRIPTOR_H
#define BEACON_IL_FACTOR_INVOKE_SUBSCRIPT_DESCRIPTOR_H

struct operator_overload;
struct SymbolEntry;
struct field;
struct property;

typedef enum subscript_tag {
	SUBSCRIPT_LOCAL_T,
	SUBSCRIPT_FIELD_T,
	SUBSCRIPT_PROPERTY_T,
	SUBSCRIPT_UNDEFINED_T
} subscript_tag;

typedef struct subscript_descriptor {
	subscript_tag tag;
	struct operator_overload* opov;
	int index;
	union {
		struct SymbolEntry* local;
		struct field* fi;
		struct property* prop;
	} u;
} subscript_descriptor;

struct generic_type* subscript_descriptor_receiver(const subscript_descriptor* desc);
#endif