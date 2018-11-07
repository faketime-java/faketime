#include <stdlib.h>
#include <string.h>
#include "jvmti.h"
#include "macros.c"

static jvmtiEnv *jvmti = NULL;
static jobject (*realMethods[301])(JNIEnv *, jobject, void *, void *, void *, void *, void *, void *, void *, void *, void *, void *);
static jmethodID realMethodIds[301];
static int realMethodIndex = 0;

static int currentTimeMillisMethodIndex = -1;
static jobject (*fakeCurrentTimeMillisReturningObject)(JNIEnv *, jobject);
static jlong (*realCurrentTimeMillis)(JNIEnv *, jobject);

static int getNanoTimeAdjustmentMethodIndex = -1;
static jobject (*fakeGetNanoTimeAdjustmentReturningObject)(JNIEnv *, jobject, jlong);
static jlong (*realGetNanoTimeAdjustment)(JNIEnv *, jobject, jlong);

generateFakeMethods

jstring getSystemProperty(JNIEnv *jni_env, const char *name) {
  jclass systemClass = (*jni_env)->FindClass(jni_env, "java/lang/System");
  return (*jni_env)->CallStaticObjectMethod(jni_env,
                                            systemClass,
                                            (*jni_env)->GetStaticMethodID(jni_env, systemClass, "getProperty", "(Ljava/lang/String;)Ljava/lang/String;"),
                                            (*jni_env)->NewStringUTF(jni_env, name));
}

jstring getAbsoluteSystemProperty(JNIEnv *jni_env) {
  return getSystemProperty(jni_env, "faketime.absolute.ms");
}

jstring getOffsetSystemProperty(JNIEnv *jni_env) {
  return getSystemProperty(jni_env, "faketime.offset.ms");
}

jlong fakeCurrentTimeMillis(JNIEnv *jni_env, jobject object) {
  jstring absoluteValueString = getAbsoluteSystemProperty(jni_env);

  if (absoluteValueString != NULL) {
    const char *absoluteValueStringChars = (*jni_env)->GetStringUTFChars(jni_env, absoluteValueString, NULL);
    jlong time = strtoll(absoluteValueStringChars, NULL, 10);
    (*jni_env)->ReleaseStringUTFChars(jni_env, absoluteValueString, absoluteValueStringChars);
    return time;
  }

  jstring offsetValueString = getOffsetSystemProperty(jni_env);

  if (offsetValueString != NULL) {
    const char *offsetValueStringChars = (*jni_env)->GetStringUTFChars(jni_env, offsetValueString, NULL);
    jlong time = realCurrentTimeMillis(jni_env, object) + strtoll(offsetValueStringChars, NULL, 10);
    (*jni_env)->ReleaseStringUTFChars(jni_env, offsetValueString, offsetValueStringChars);
    return time;
  }

  return realCurrentTimeMillis(jni_env, object);
}

jlong fakeGetNanoTimeAdjustment(JNIEnv *jni_env, jobject object, jlong offsetInSeconds) {
  jstring absoluteValueString = getAbsoluteSystemProperty(jni_env);

  if (absoluteValueString != NULL) {
    const char *absoluteValueStringChars = (*jni_env)->GetStringUTFChars(jni_env, absoluteValueString, NULL);
    jlong time = strtoll(absoluteValueStringChars, NULL, 10);
    (*jni_env)->ReleaseStringUTFChars(jni_env, absoluteValueString, absoluteValueStringChars);
    return (time - offsetInSeconds * 1000) * 1000000;
  }

  return realGetNanoTimeAdjustment(jni_env, object, offsetInSeconds);
}

void JNICALL onNativeMethodBind(jvmtiEnv *jvmti_env, JNIEnv* jni_env, jthread thread, jmethodID method, void* address, void** new_address_ptr) {
  if (realCurrentTimeMillis != NULL) {
    return;
  }

  char *methodName = NULL;

  if ((*jvmti)->GetMethodName(jvmti, method, &methodName, NULL, NULL) == JVMTI_ERROR_NONE) {
    // java 8
    if (strcmp("currentTimeMillis", methodName) == 0) {
      realCurrentTimeMillis = address;
      *new_address_ptr = &fakeCurrentTimeMillis;
    }
  } else {
    // java > 8
    switch (realMethodIndex) {
      generateFakeMethodCases
      default:
        break;
    }

    realMethodIds[realMethodIndex] = method;
    realMethodIndex++;
  }
}

void JNICALL onVmInit(jvmtiEnv *jvmti_env, JNIEnv* jni_env, jthread thread) {
  if (realCurrentTimeMillis != NULL) {
    return;
  }

  int i;

  for (i = 0; i < realMethodIndex; i++) {
    char *methodName = NULL;
    jvmtiError err = (*jvmti)->GetMethodName(jvmti, realMethodIds[i], &methodName, NULL, NULL);

    if (err != JVMTI_ERROR_NONE) {
      fprintf(stderr, "FakeTime agent failed to get native method name");
      return;
    }

    if (strcmp("currentTimeMillis", methodName) == 0) {
      currentTimeMillisMethodIndex = i;
      fakeCurrentTimeMillisReturningObject = (void *)fakeCurrentTimeMillis;
      realCurrentTimeMillis = (void *)realMethods[i];
    } else if (strcmp("getNanoTimeAdjustment", methodName) == 0) {
      getNanoTimeAdjustmentMethodIndex = i;
      fakeGetNanoTimeAdjustmentReturningObject = (void *)fakeGetNanoTimeAdjustment;
      realGetNanoTimeAdjustment = (void *)realMethods[i];
    }
  }
}

JNIEXPORT jint JNICALL Agent_OnLoad(JavaVM *jvm, char *options, void *reserved) {
  if ((*jvm)->GetEnv(jvm, (void **)&jvmti, JVMTI_VERSION_1_0) != JNI_OK || jvmti == NULL) {
    fprintf(stderr, "FakeTime agent failed to get JVMTI");
    return JNI_ERR;
  }

  jvmtiEventCallbacks callbacks;
  memset(&callbacks, 0, sizeof(callbacks));
  callbacks.NativeMethodBind = &onNativeMethodBind;
  callbacks.VMInit = &onVmInit;

  if ((*jvmti)->SetEventCallbacks(jvmti, &callbacks, sizeof(callbacks)) != JVMTI_ERROR_NONE) {
    fprintf(stderr, "FakeTime agent failed to set JVMTI callbacks");
    return JNI_ERR;
  }

  jvmtiCapabilities capabilities;
  memset(&capabilities, 0, sizeof(jvmtiCapabilities));
  capabilities.can_generate_native_method_bind_events = 1;

  if ((*jvmti)->AddCapabilities(jvmti, &capabilities) != JVMTI_ERROR_NONE) {
    fprintf(stderr, "FakeTime agent failed to get necessary JVMTI capabilities");
    return JNI_ERR;
  }

  if ((*jvmti)->SetEventNotificationMode(jvmti, JVMTI_ENABLE, JVMTI_EVENT_NATIVE_METHOD_BIND, NULL) != JVMTI_ERROR_NONE) {
    fprintf(stderr, "FakeTime agent failed to set event notification");
    return JNI_ERR;
  }

  if ((*jvmti)->SetEventNotificationMode(jvmti, JVMTI_ENABLE, JVMTI_EVENT_VM_INIT, NULL) != JVMTI_ERROR_NONE) {
    fprintf(stderr, "FakeTime agent failed to set event notification");
    return JNI_ERR;
  }

  return JNI_OK;
}
