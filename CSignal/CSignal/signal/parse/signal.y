%{
#include <stdio.h>
#include <stdlib.h>
#include "../ast/ast_new_operator.h"
#include "../ast/ast_new_stmt.h"
#include "../ast/ast_new_decl.h"
#include "../ast/constructor_chain_type.h"
#include "../ast/assign_operator_type.h"
#include "../ast/modifier_type.h"
#include "../ast/access_level.h"
#define YYDEBUG 1
#define YYERROR_VERBOSE 1
%}
%union {
	char char_value;
	const char* string_value;
	ast* ast_value;
	assign_operator_type assign_otype_value;
	constructor_chain_type chain_type_value;
	modifier_type modifier_type_value;
	access_level access_level_value;
}
%locations
%token <ast_value>			CHAR_LITERAL
%token <ast_value>			STRING_LITERAL
%token <ast_value>			INT
%token <ast_value>			DOUBLE
%token <string_value>		IDENT
%type <assign_otype_value>	assign_type_T
%type <chain_type_value>	constructor_chain_type_T
%type <access_level_value>	access_level_T
%type <modifier_type_value> modifier_type_T;
%token DOT COMMA COLON COLO_COLO
		ADD SUB MUL DIV MOD NOT
		ASSIGN ADD_ASSIGN SUB_ASSIGN MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN
		EQUAL NOTEQUAL
		INC DEC
		GT GE LT LE
		BIT_AND LOGIC_AND BIT_OR LOGIC_OR
		LCB RCB LRB RRB LSB RSB
		SEMI IMPORT
		THIS SUPER
		CLASS PUBLIC PRIVATE PROTECTED STATIC NATIVE NEW
		DEF ARROW NAMESPACE
		IF ELIF ELSE
%type <ast_value> root 
					top_level 
					namespace_decl
					namespace_body
					namespace_member_decl_list
					namespace_member_decl
					namespace_member_decl_optional
					namespace_path
					import 
					class_decl 
						class_super 
						member_define_list
						member_define
						constructor_define
						constructor_chain
						constructor_chain_optional
						func_define
						field_define
						parameter_list
						argument_list
					expression 
						assign 
						or 
						and 
						equal 
						compare 
						addsub 
						muldiv 
						unary 
						prefix 
						postfix 
						primary
					stmt_list
						stmt
						variable_stmt
						if_stmt
							elif_list
							elif
						scope
						scope_optional
%%
root
	: top_level
	| root top_level
	| error '\n'
	{
		$$ = ast_new_blank();
	}
	;
top_level
	: expression
	{
		ast_compile_entry($1);
	}
	| stmt
	{
		ast_compile_entry($1);
	}
	| import
	{
		ast_compile_entry($1);
	}
	| namespace_decl
	{
		ast_compile_entry($1);
	}
	;
namespace_decl
	: NAMESPACE namespace_path namespace_body
	{
		$$ = ast_new_namespace_decl($2, $3);
	}
	;
namespace_body
	: LCB namespace_member_decl_optional RCB
	{
		$$ = $2
	}
	;
namespace_member_decl
	: NAMESPACE namespace_path namespace_body
	{
		$$ = ast_new_namespace_namespace_decl($2, $3);
	}
	| class_decl
	{
		$$ = $1;
	}
	;
namespace_member_decl_list
	: namespace_member_decl
	{
		$$ = $1
	}
	| namespace_member_decl_list namespace_member_decl
	{
		$$ = ast_new_namespace_member_decl_list($1, $2);
	}
	;
namespace_member_decl_optional
	: /* empty */
	{
		$$ = ast_new_blank();
	}
	| namespace_member_decl_list
	{
		$$ = $1
	}
	;
namespace_path
	: IDENT
	{
		$$ = ast_new_namespace_path($1);
	}
	| namespace_path DOT IDENT
	{
		$$ = ast_new_namespace_path_list($1, $3);
	}
	;
import
	: IMPORT STRING_LITERAL
	{
		$$ = ast_new_import_decl(ast_new_import_path($2));
	}
	;
class_decl
	: CLASS IDENT class_super LCB member_define_list RCB
	{
		$$ = ast_new_class_decl($2, $3, $5);
	}
	;
class_super
	: /* empty */
	{
		$$ = ast_new_blank();
	}
	| COLON IDENT
	{
		$$ = ast_new_superclass($2);
	}
	;
member_define_list
	: /* empty */
	{
		$$ = ast_new_blank();
	}
	| member_define
	{
		$$ = ast_new_member_decl($1);
	}
	| member_define_list member_define
	{
		$$ = ast_new_member_decl_list($1, ast_new_member_decl($2));
	}
	;
member_define
	: constructor_define
	| func_define
	| field_define
	;
constructor_define
	: DEF NEW LRB parameter_list RRB constructor_chain_optional scope_optional
	{
		$$ = ast_new_constructor_decl($4, $6, $7);
	}
	| DEF NEW LRB RRB constructor_chain_optional scope_optional
	{
		$$ = ast_new_constructor_decl(ast_new_blank(), $5, $6);
	}
	;
constructor_chain
	: COLON constructor_chain_type_T LRB argument_list RRB
	{
		$$ = ast_new_constructor_chain($2, $4);
	}
	| COLON constructor_chain_type_T LRB RRB
	{
		$$ = ast_new_constructor_chain($2, ast_new_blank());
	}
	;
constructor_chain_type_T
	: SUPER
	{
		$$ = chain_type_super;
	}
	| THIS
	{
		$$ = chain_type_this;
	}
	;
constructor_chain_optional
	: /* empty */
	{
		$$ = ast_new_blank();
	}
	| constructor_chain
	;
func_define
	: DEF IDENT LRB parameter_list RRB ARROW IDENT scope_optional
	{
		$$ = ast_new_function_decl($2, $4, $8, $7);
	}
	| DEF IDENT LRB RRB ARROW IDENT scope_optional
	{
		$$ = ast_new_function_decl_empty_params($2, $7, $6);
	}
	;
field_define
	: IDENT IDENT SEMI
	{
		$$ = ast_new_field_decl($1, $2);
	}
	;
modifier_type_T
	: STATIC
	{
		$$ = modifier_static;
	}
	| NATIVE
	{
		$$ = modifier_native;
	}
	;
access_level_T
	: PUBLIC
	{
		$$ = access_public;
	}
	| PRIVATE
	{
		$$ = access_private;
	}
	| PROTECTED
	{
		$$ = access_protected;
	}
	;
parameter_list
	: IDENT IDENT
	{
		$$ = ast_new_parameter($1, $2);
	}
	| IDENT IDENT COMMA parameter_list
	{
		$$ = ast_new_parameter_list($1, $2, $4)
	}
	;
argument_list
	: expression
	{
		$$ = ast_new_argument($1);
	}
	| expression COMMA argument_list
	{
		$$ = ast_new_argument_list(ast_new_argument($1), $3);
	}
	;
expression
	: assign
	;
assign
	: or
	| or assign_type_T assign
	{
		$$ = ast_new_generic_assign($1, $2, $3);
	}
	;
assign_type_T
	: ASSIGN
	{
		$$ = assign_otype_def;
	}
	| ADD_ASSIGN
	{
		$$ = assign_otype_add;
	}
	| SUB_ASSIGN
	{
		$$ = assign_otype_sub;
	}
	| MUL_ASSIGN
	{
		$$ = assign_otype_mul;
	}
	| DIV_ASSIGN
	{
		$$ = assign_otype_div;
	}
	| MOD_ASSIGN
	{
		$$ = assign_otype_mod;
	}
	;
or
	: and
	| or BIT_OR and
	{
		$$ = ast_new_bit_or($1, $3);
	}
	| or LOGIC_OR and
	{
		$$ = ast_new_logic_or($1, $3);
	}
	;
and
	: equal
	| and BIT_AND equal
	{
		$$ = ast_new_bit_and($1, $3);
	}
	| and LOGIC_AND equal
	{
		$$ = ast_new_logic_and($1, $3);
	}
	;
equal
	: compare
	| equal EQUAL compare
	{
		$$ = ast_new_equal($1, $3);
	}
	| equal NOTEQUAL compare
	{
		$$ = ast_new_notequal($1, $3);
	}
	;
compare
	: addsub
	| compare GT addsub
	{
		$$ = ast_new_gt($1, $3);
	}
	| compare GE addsub
	{
		$$ = ast_new_ge($1, $3);
	}
	| compare LT addsub
	{
		$$ = ast_new_lt($1, $3);
	}
	| compare LE addsub
	{
		$$ = ast_new_le($1, $3);
	}
	;
addsub
	: muldiv
	| addsub ADD muldiv
	{
		$$ = ast_new_add($1, $3);
	}
	| addsub SUB muldiv
	{
		$$ = ast_new_sub($1, $3);
	}
	;
muldiv
	: unary
	| muldiv MUL unary
	{
		$$ = ast_new_mul($1, $3);
	}
	| muldiv DIV unary
	{
		$$ = ast_new_div($1, $3);
	}
	| muldiv MOD unary
	{
		$$ = ast_new_mod($1, $3);
	}
	;
unary
	: prefix
	| NOT unary
	{
		$$ = ast_new_not($2);
	}
	| SUB unary
	{
		$$ = ast_new_neg($2);
	}
	;
prefix
	: postfix
	| INC postfix
	{
		$$ = ast_new_pre_inc($2);
	}
	| DEC postfix
	{
		$$ = ast_new_pre_dec($2);
	}
	;
postfix
	: primary
	| postfix DOT IDENT LRB RRB
	{
		$$ = ast_new_invoke($1, $3, ast_new_blank());
	}
	| postfix DOT IDENT LRB argument_list RRB
	{
		$$ = ast_new_invoke($1, $3, $5);
	}
	| postfix INC
	{
		$$ = ast_new_post_inc($1);
	}
	| postfix DEC
	{
		$$ = ast_new_post_dec($1);
	}
	;
primary
	: INT
	| DOUBLE
	| CHAR_LITERAL
	| STRING_LITERAL
	| IDENT
	{
		$$ = ast_new_variable($1);
	}
	| IDENT LRB RRB
	{
		$$ = ast_new_call($1, ast_new_blank());
	}
	| IDENT LRB argument_list RRB
	{
		$$ = ast_new_call($1, $3);
	}
	| LRB expression RRB
	{
		$$ = $2;
	}
	;
stmt_list
	: stmt
	{
		$$ = ast_new_stmt($1);
	}
	| stmt_list stmt
	{
		$$ = ast_new_stmt_list($1, $2);
	}
	;
stmt
	: expression SEMI
	{
		$$ = ast_new_proc($1);
	}
	| variable_stmt
	| if_stmt
	;
variable_stmt
	: IDENT IDENT ASSIGN expression SEMI
	{
		$$ = ast_new_variable_decl(ast_new_typename($1), ast_new_identifier($2), $4);
	}
	;
if_stmt
	: IF LRB expression RRB scope
	{
		$$ = ast_new_if($3, $5);
	}
	| IF LRB expression RRB scope ELSE scope
	{
		$$ = ast_new_if_else($3, $5, $7);
	}
	| IF LRB expression RRB scope elif_list
	{
		$$ = ast_new_if_elif_list($3, $5, $6);
	}
	| IF LRB expression RRB scope elif_list ELSE scope
	{
		$$ = ast_new_if_elif_list_else($3, $5, $6, $8);
	}
	;
elif_list
	: elif
	| elif_list elif
	{
		$$ = ast_new_elif_list($1, $2);
	}
	;
elif
	: ELIF LRB expression RRB scope
	{
		$$ = ast_new_elif($3, $5);
	}
	;
scope
	: LCB stmt_list RCB
	{
		$$ = ast_new_scope($2);
	}
	| LCB RCB
	{
		$$ = ast_new_scope_empty();
	}
	;
scope_optional
	: SEMI
	{
		$$ = ast_new_blank();
	}
	| scope
	;
%%