#include <stdlib.h>
#include <stdio.h>
#include "mem.h"
#include "text.h"

#if defined(_MSC_VER)
#include <crtdbg.h>
#endif

#include <assert.h>
#include <string.h>

#if defined(_WIN32)
#include <Windows.h>
#endif

static void* default_realloc(void * block, size_t newSize, const char * filename, int lineno);
static slot* slot_create_or_add(size_t size);
static slot* slot_new();
static void slot_check_init(const char* filename, int lineno, void* arena, size_t size);
static void slot_add(slot* head, slot* a);
static void* slot_realloc(slot* head, void* arena, size_t newSize);
static int slot_remove(slot* head, void* arena);
static void slot_dump(slot* self);
static void slot_destroy(slot* self);

static slot* slot_find(slot* head, void* arena);
static slot* slot_last(slot* head);

static void mem_input();
static char* mem_readline();

static slot* gSlotHead = NULL;
static bool gMemTrace = false;
static int gMemCounter = 0;
static int gMemNotFoundRealloc = 0;
static int gMemNotFoundFree = 0;
static int gMemUsedMemory = 0;
static int gMemBreak = -1;

void * mem_malloc(size_t size, const char * filename, int lineno) {
	void* ret = malloc(size);
	if (gMemTrace) {
		slot_check_init(filename, lineno, ret, size);
	}
	if (ret == NULL) {
		exit(1);
	}
	memset(ret, 0, size);
	return ret;
}

void * mem_realloc(void * block, size_t newSize, const char * filename, int lineno) {
	if (gMemTrace) {
		return slot_realloc(gSlotHead, block, newSize);
	} else {
		return default_realloc(block, newSize, filename, lineno);
	}
}

void mem_free(void * block, const char * filename, int lineno) {
	if (block == NULL) {
		return;
	}
	int index = -1;
	if (gMemTrace) {
		index = slot_remove(gSlotHead, block);
	}
	free(block);
}

void mem_dump() {
	if (!gMemTrace) {
		return;
	}
	text_printfln(" - memory leaks(%d) -", gMemCounter);
	text_printfln("    used memory(%d)", gMemUsedMemory);
	text_printfln("    not found realloc(%d)", gMemNotFoundRealloc);
	text_printfln("    not found free(%d)", gMemNotFoundFree);

	if(gSlotHead == NULL) { return; }
	slot* ptr = gSlotHead->next;
	while (ptr != NULL) {
		text_printf("    ");
		slot_dump(ptr);
		text_printf("\n");
		ptr = ptr->next;
	}
}

void mem_set_trace(bool trace) {
	gMemTrace = trace;
}

void mem_mark(void* p, size_t size, const char* filename, int lineno) {
	if (p == NULL) {
		return;
	}
	if (gMemTrace) {
		slot_check_init(filename, lineno, p, size);
	}
}

bool mem_get_trace() {
	return gMemTrace;
}

void mem_break(int count) {
	gMemBreak = count;
}

void mem_destroy() {
	if (!gMemTrace || gSlotHead == NULL) {
		return;
	}
	slot_destroy(gSlotHead->next);
	gSlotHead = NULL;
}

//private
static void* default_realloc(void * block, size_t newSize, const char * filename, int lineno) {
	void* ret = realloc(block, newSize);
	//allocCount++;
	return ret;
}

static slot* slot_new() {
	slot* ret = (slot*)malloc(sizeof(slot));
	ret->filename = NULL;
	ret->lineno = -1;
	ret->size = -1;
	ret->prev = NULL;
	ret->next = NULL;
	ret->index = 0;
	return ret;
}

static void slot_check_init(const char* filename, int lineno, void* arena, size_t size) {
	//スロットの作成
	assert(arena != NULL);
	slot* ptr = slot_create_or_add(size);
	ptr->filename = filename;
	ptr->lineno = lineno;
	ptr->arena = arena;
	ptr->size = size;
}

static slot* slot_create_or_add(size_t size) {
	slot* ptr = NULL;
	if (gSlotHead == NULL) {
		//まだ連結リストの先頭を作っていないならそれを作って返す
		gSlotHead = slot_new();
		ptr = gSlotHead;
		gMemCounter = 1;
		gMemNotFoundRealloc = 0;
		gMemNotFoundFree = 0;
		gMemUsedMemory = size;
		return ptr;
	}
	//連結リストにくっつけて返す
	ptr = slot_new();
	slot_add(gSlotHead, ptr);

	gMemCounter++;
	gMemUsedMemory += size;
	ptr->index = gMemCounter;
	if (ptr->index == gMemBreak) {
		mem_input();
	}
	return ptr;
}

static void slot_add(slot* head, slot* a) {
	slot* last = slot_last(head);
	last->next = a;
	a->prev = last;
}

static void* slot_realloc(slot* head, void* arena, size_t newSize) {
	//arenaがmem_mallocによって確保されたものではないなら、
	//適当に拡張して返す
	slot* ptr = slot_find(head, arena);
	if(ptr == NULL) {
		void* ret = realloc(arena, newSize);
		assert(ret != NULL);
		gMemNotFoundRealloc++;
		return ret;
	}
	//mem_mallocによって確保されたなら、
	//差分を記録する
	void* temp = realloc(arena, newSize);
	assert(temp != NULL);
	//縮んだ
	if (ptr->size > newSize) {
		gMemUsedMemory -= (ptr->size - newSize);
	//拡大した
	} else if (ptr->size < newSize) {
		gMemUsedMemory += (newSize - ptr->size);
		memset(temp + ptr->size, 0, newSize - ptr->size);
	}
	ptr->arena = temp;
	ptr->size = newSize;
	return temp;
}

static int slot_remove(slot* head, void* arena) {
	if (head == NULL) {
		return -1;
	}
	//mem_mallocによって確保されたものではないなら、
	//何もしない
	slot* ptr = slot_find(head, arena);
	if(ptr == NULL) {
		gMemNotFoundFree++;
		return -1;
	}
	//スロットを削除するために、
	//前と後ろを切り離す
	if (ptr->prev != NULL) {
		ptr->prev->next = ptr->next;
	}
	if (ptr->next != NULL) {
		ptr->next->prev = ptr->prev;
	}
	int ret = ptr->index;
	gMemCounter--;
	gMemUsedMemory -= ptr->size;
	if(ptr == gSlotHead) {
		//ちゃんとメモリリークがなく全て実行されるとここにくる
		gSlotHead = gSlotHead->next;
		free(ptr);
	} else {
		free(ptr);
	}
	assert(gMemCounter >= 0);
	return ret;
}

static void slot_dump(slot* self) {
	text_printf("%p", self->arena);
	text_printf("(%d)", self->size);
	text_printf("@%d", self->index);
	text_printf(" %s", self->filename);
	text_printf("<%d>", self->lineno);
}

static void slot_destroy(slot* self) {
	if (self == NULL) {
		return;
	}
	slot* ptr = self;
	while (true) {
		ptr->filename = NULL;

		slot* next = NULL;
		if (ptr->next == NULL) {
			free(ptr);
		} else {
			slot* temp = ptr->next;
			free(ptr);
			next = temp;
		}
		if (next == NULL) {
			break;
		}
		ptr = next;
	}
}

static slot* slot_find(slot* head, void* arena) {
	slot* ptr = head;
	while (ptr->arena != arena) {
		ptr = ptr->next;
		//mem_malloc以外で確保されたメモリ
		if (ptr == NULL) {
			//void* ret = realloc(arena, newSize);
			//assert(ret != NULL);
			//gMemNotFoundRealloc++;
			//return ret;
			break;
		}
	}
	return ptr;
}

static slot* slot_last(slot* head) {
	slot* ptr = head;
	while (ptr->next != NULL) {
		assert((ptr != NULL && ptr->arena != NULL));
		ptr = ptr->next;
	}
	return ptr;
}

static void mem_input() {
	int breakNow = 1;
	text_printfln("stop program!");
	/*
	while (breakNow != 0) {
		char* line = mem_readline();
		bool breakLoop = false;
		//コマンドを解釈
		if (!strcmp(line, "stop")) {
			breakLoop = true;
		} else if(!strcmp(line, "ignore")) {
			breakLoop = true;
		} else {
			text_printfln("undefined command: %s", line);
		}
		free(line);
		if (breakLoop) {
			break;
		}
	}
	*/
}

static char* mem_readline() {
	char* line = malloc(sizeof(char) * 16);
	int offs = 0;
	int len = 16;
	while (true) {
		char c = getc(stdin);
		//改行文字なら終了
		if (c == '\n') {
			break;
		}
		//まだバッファに余りがあある
		if (offs < len) {
			line[offs] = c;
			offs++;
		//もうないので拡張
		} else if (offs >= len) {
			int newLen = len + (len / 2);
			void* temp = realloc(line, sizeof(char) * newLen);
			assert(temp != NULL);
			line = temp;

			line[offs] = c;
			len = newLen;
			offs++;
		}
	}
	return line;
}