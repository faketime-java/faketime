#include <stdlib.h>
#include <string.h>
#include "jvmti.h"

typedef struct {
  jmethodID method;
  void *address;
} method_entry;

#define MAX_METHOD_ENTRIES 512
static method_entry methodEntries[MAX_METHOD_ENTRIES];
static int methodEntryIndex = 0;

static jvmtiEnv *jvmti = NULL;

static jlong (*realCurrentTimeMillis)(JNIEnv *, jclass);
static jlong (*realGetNanoTimeAdjustment)(JNIEnv *, jclass, jlong);

jstring getSystemProperty(JNIEnv *jni_env, const char *name) {
  jclass systemClass = (*jni_env)->FindClass(jni_env, "java/lang/System");
  return (*jni_env)->CallStaticObjectMethod(jni_env,
                                            systemClass,
                                            (*jni_env)->GetStaticMethodID(jni_env, systemClass, "getProperty", "(Ljava/lang/String;)Ljava/lang/String;"),
                                            (*jni_env)->NewStringUTF(jni_env, name));
}

int getAbsoluteFromSystemProperty(JNIEnv *jni_env, jlong *result) {
  jstring stringValue = getSystemProperty(jni_env, "faketime.absolute.ms");

  if (stringValue != NULL) {
    const char *stringChars = (*jni_env)->GetStringUTFChars(jni_env, stringValue, NULL);
    jlong longValue = strtoll(stringChars, NULL, 10);
    (*jni_env)->ReleaseStringUTFChars(jni_env, stringValue, stringChars);
    *result = longValue;
    return 1;
  }

  return 0;
}

int getOffsetFromSystemProperty(JNIEnv *jni_env, jlong *result) {
  jstring stringValue = getSystemProperty(jni_env, "faketime.offset.ms");

  if (stringValue != NULL) {
    const char *stringChars = (*jni_env)->GetStringUTFChars(jni_env, stringValue, NULL);
    jlong longValue = strtoll(stringChars, NULL, 10);
    (*jni_env)->ReleaseStringUTFChars(jni_env, stringValue, stringChars);
    *result = longValue;
    return 1;
  }

  return 0;
}

jlong fakeCurrentTimeMillis(JNIEnv *jni_env, jclass klass) {
  jlong propertyValue;

  if (getAbsoluteFromSystemProperty(jni_env, &propertyValue)) {
    return propertyValue;
  }
  else if (getOffsetFromSystemProperty(jni_env, &propertyValue)) {
    return realCurrentTimeMillis(jni_env, klass) + propertyValue;
  }

  return realCurrentTimeMillis(jni_env, klass);
}

jlong fakeGetNanoTimeAdjustment(JNIEnv *jni_env, jclass klass, jlong offsetInSeconds) {
  jlong propertyValue;

  if (getAbsoluteFromSystemProperty(jni_env, &propertyValue)) {
    return (propertyValue - offsetInSeconds * 1000) * 1000000;
  }
  else if (getOffsetFromSystemProperty(jni_env, &propertyValue)) {
    return realGetNanoTimeAdjustment(jni_env, klass, offsetInSeconds) + propertyValue * 1000000;
  }

  return realGetNanoTimeAdjustment(jni_env, klass, offsetInSeconds);
}

void JNICALL onNativeMethodBind(jvmtiEnv *jvmti_env, JNIEnv *jni_env, jthread thread, jmethodID method, void *address, void **new_address_ptr) {
  if (realCurrentTimeMillis == NULL && methodEntryIndex < MAX_METHOD_ENTRIES) {
    methodEntries[methodEntryIndex++] = (method_entry) { .address = address, .method = method };
  }
}

void *patchNative(JNIEnv *jni_env, char *className, char *methodName, char *methodSignature, void *nativeMethodPtr) {
  jclass klass = (*jni_env)->FindClass(jni_env, className);

  if ((*jni_env)->ExceptionCheck(jni_env)) {
    // In case of NoClassDefFoundError (jdk/internal/misc/VM does't exist on Java < 9)
    (*jni_env)->ExceptionClear(jni_env);
    return NULL;
  }

  if (klass) {
    jmethodID method = (*jni_env)->GetStaticMethodID(jni_env, klass, methodName, methodSignature);

    if (method) {
      int i = 0;

      for (; i < methodEntryIndex; i++) {
        if (methodEntries[i].method == method) {
          JNINativeMethod native;
          native.fnPtr = nativeMethodPtr;
          native.name = methodName;
          native.signature = methodSignature;
          (*jni_env)->RegisterNatives(jni_env, klass, &native, 1);

          return methodEntries[i].address;
        }
      }
    }
  }

  return NULL;
}

void JNICALL onVmInit(jvmtiEnv *jvmti_env, JNIEnv *jni_env, jthread thread) {
  realCurrentTimeMillis = patchNative(jni_env, "java/lang/System", "currentTimeMillis", "()J", fakeCurrentTimeMillis);
  realGetNanoTimeAdjustment = patchNative(jni_env, "jdk/internal/misc/VM", "getNanoTimeAdjustment", "(J)J", fakeGetNanoTimeAdjustment);

  if (realCurrentTimeMillis == NULL) {
    fprintf(stderr, "FakeTime agent failed to patch currentTimeMillis.\n");
    return;
  }
  
  if (realGetNanoTimeAdjustment == NULL) {
    fprintf(stderr, "FakeTime agent failed to patch getNanoTimeAdjustment.\n");
    return;
  }
}

JNIEXPORT jint JNICALL Agent_OnLoad(JavaVM *jvm, char *options, void *reserved) {
  if (jvmti != NULL) {
    return JNI_OK;
  }

  if ((*jvm)->GetEnv(jvm, (void **)&jvmti, JVMTI_VERSION_1_0) != JNI_OK || jvmti == NULL) {
    fprintf(stderr, "FakeTime agent failed to get JVMTI.\n");
    return JNI_ERR;
  }

  jvmtiEventCallbacks callbacks;
  memset(&callbacks, 0, sizeof(callbacks));
  callbacks.NativeMethodBind = &onNativeMethodBind;
  callbacks.VMInit = &onVmInit;

  if ((*jvmti)->SetEventCallbacks(jvmti, &callbacks, sizeof(callbacks)) != JVMTI_ERROR_NONE) {
    fprintf(stderr, "FakeTime agent failed to set JVMTI callbacks.\n");
    return JNI_ERR;
  }

  jvmtiCapabilities capabilities;
  memset(&capabilities, 0, sizeof(jvmtiCapabilities));
  capabilities.can_generate_native_method_bind_events = 1;

  if ((*jvmti)->AddCapabilities(jvmti, &capabilities) != JVMTI_ERROR_NONE) {
    fprintf(stderr, "FakeTime agent failed to get necessary JVMTI capabilities.\n");
    return JNI_ERR;
  }

  if ((*jvmti)->SetEventNotificationMode(jvmti, JVMTI_ENABLE, JVMTI_EVENT_NATIVE_METHOD_BIND, NULL) != JVMTI_ERROR_NONE) {
    fprintf(stderr, "FakeTime agent failed to set event notification.\n");
    return JNI_ERR;
  }

  if ((*jvmti)->SetEventNotificationMode(jvmti, JVMTI_ENABLE, JVMTI_EVENT_VM_INIT, NULL) != JVMTI_ERROR_NONE) {
    fprintf(stderr, "FakeTime agent failed to set event notification.\n");
    return JNI_ERR;
  }

  return JNI_OK;
}
