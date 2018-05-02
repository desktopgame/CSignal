#include "il_stmt_defer_impl.h"
#include "../../util/mem.h"
#include "../../util/text.h"

il_stmt* il_stmt_wrap_defer(il_stmt_defer* self) {
	il_stmt* ret = (il_stmt*)MEM_MALLOC(sizeof(il_stmt));
	ret->type = ilstmt_defer;
	ret->u.defer_ = self;
	return ret;
}

il_stmt_defer* il_stmt_defer_new() {
	il_stmt_defer* ret = (il_stmt_defer*)MEM_MALLOC(sizeof(il_stmt_defer));
	ret->stmt = NULL;
	return ret;
}

void il_stmt_defer_dump(il_stmt_defer* self, int depth) {
	text_putindent(depth);
	text_printfln("defer");
	il_stmt_dump(self->stmt, depth + 1);
}

void il_stmt_defer_load(il_stmt_defer* self, enviroment* env, il_context* ilctx) {
	il_stmt_load(self->stmt, env, ilctx);
}

void il_stmt_defer_generate(il_stmt_defer* self, enviroment* env, il_context* ilctx) {

}

void il_stmt_defer_delete(il_stmt_defer* self) {
	il_stmt_delete(self->stmt);
	MEM_FREE(self);
}