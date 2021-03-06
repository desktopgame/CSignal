#include "jp_koya_jbeacon_Beacon.h"
#include "../../util/string_pool.h"
#include "../../env/script_context.h"
#include "../../vm/eval.h"

JNIEXPORT void JNICALL Java_jp_koya_jbeacon_Beacon_nativeInit(JNIEnv * env, jclass cls) {
	string_pool_init();
	script_context_open();
}

JNIEXPORT void JNICALL Java_jp_koya_jbeacon_Beacon_nativeDestroy(JNIEnv * env, jclass cls) {
	script_context_close();
	string_pool_destroy();
}