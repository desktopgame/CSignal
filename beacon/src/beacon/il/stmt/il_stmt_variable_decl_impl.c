#include "il_stmt_variable_decl_impl.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../../vm/enviroment.h"
#include "../../env/namespace.h"
#include "../../env/class_loader.h"
#include "../../env/import_manager.h"

il_stmt * il_stmt_wrap_variable_decl(il_stmt_variable_decl * self) {
	il_stmt* ret = il_stmt_new(ilstmt_variable_decl);
	ret->u.variable_decl = self;
	return ret;
}

il_stmt_variable_decl * il_stmt_variable_decl_new(string_view namev) {
	il_stmt_variable_decl* ret = (il_stmt_variable_decl*)MEM_MALLOC(sizeof(il_stmt_variable_decl));
	ret->namev = namev;
	ret->fqcn = generic_cache_new();
	return ret;
}

void il_stmt_variable_decl_dump(il_stmt_variable_decl * self, int depth) {
	text_putindent(depth);
	text_printf("variable decl %s", string_pool_ref2str(self->namev));
	text_putline();

	generic_cache_dump(self->fqcn, depth + 1);
}

void il_stmt_variable_decl_generate(il_stmt_variable_decl * self, enviroment * env, call_context* cctx) {

}

void il_stmt_variable_decl_load(il_stmt_variable_decl * self, struct enviroment* env, call_context* cctx) {
	if(symbol_table_contains(env->sym_table, self->namev)) {
		bc_error_throw(bcerror_overwrap_variable_name,
			string_pool_ref2str(self->namev)
		);
	}
	symbol_table_entry(
		env->sym_table,
		import_manager_resolve(NULL, NULL, self->fqcn, cctx),
		self->namev
	);
}

void il_stmt_variable_decl_delete(il_stmt_variable_decl * self) {
	if (self == NULL) {
		return;
	}
	MEM_FREE(self);
}
