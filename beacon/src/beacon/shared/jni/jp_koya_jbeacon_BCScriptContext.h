/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class jp_koya_jbeacon_BCScriptContext */

#ifndef _Included_jp_koya_jbeacon_BCScriptContext
#define _Included_jp_koya_jbeacon_BCScriptContext
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     jp_koya_jbeacon_BCScriptContext
 * Method:    nativeOpen
 * Signature: ()Ljp/koya/jbeacon/BCScriptContext;
 */
JNIEXPORT jobject JNICALL Java_jp_koya_jbeacon_BCScriptContext_nativeOpen
  (JNIEnv *, jclass);

/*
 * Class:     jp_koya_jbeacon_BCScriptContext
 * Method:    nativeClose
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_jp_koya_jbeacon_BCScriptContext_nativeClose
  (JNIEnv *, jclass);

/*
 * Class:     jp_koya_jbeacon_BCScriptContext
 * Method:    nativeGetRootNamespace
 * Signature: (Ljava/lang/String;)Ljp/koya/jbeacon/BCNamespace;
 */
JNIEXPORT jobject JNICALL Java_jp_koya_jbeacon_BCScriptContext_nativeGetRootNamespace
  (JNIEnv *, jobject, jstring);

#ifdef __cplusplus
}
#endif
#endif