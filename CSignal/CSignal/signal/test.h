#pragma once
#ifndef SIGNAL_TEST_H
#define SIGNAL_TEST_H

typedef struct OBJ {
	int index;
} OBJ;

typedef struct PERSON {
	char* name;
	int age;
} PERSON;

typedef struct HOLDER {
	union {
		int i;
		char c;
		char* s;
	} u;
} HOLDER;

/**
 * スタックのテストを実行.
 */
void test_stack(void);

/**
 * リストのテストを実行.
 */
void test_list(void);

/**
 * ASTのテストを実行.
 */
void test_ast(void);

/**
 * ASTのテストを実行.
 */
void test_ast2(void);

/**
 * tree_mapのテストを実行.
 */
void test_tree_map(void);

/**
 * 名前空間のテストを実行.
 */
void test_namespace(void);

/**
 * IOのテストを実行.
 */
void test_io(void);

void test_io2(void);

void test_file_path(void);

void test_cll(void);

void test_struct(void);

void test_vector(void);

void test_vector2(void);

void test_vector3(void);

void test_vector4(void);

void test_map(void);

void test_vm(void);

void test_vm2(void);

void test_string_table(void);

void test_preload(void);

void test_props(void);

void test_dup(void);
#endif // !SIGNAL_TEST_H
