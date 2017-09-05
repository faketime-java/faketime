#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "jvmti.h"

typedef struct {
  /* JVMTI Environment */
  jvmtiEnv      *jvmti;
  jboolean       vm_is_started;
  /* Data access Lock */
  jrawMonitorID  lock;
} GlobalAgentData;

typedef jlong (JNICALL *call__jlong) (JNIEnv*, jclass);

static jvmtiEnv *jvmti = NULL;
static GlobalAgentData *gdata;
static call__jlong realCurrentTimeInMillis = NULL;

JNIEXPORT jlong JNICALL fakeCurrentTimeInMillis(JNIEnv* env, jclass jc) {
  if (!gdata->vm_is_started) {
    return realCurrentTimeInMillis(env, jc);
  }

  char *endptr;
  jclass systemClass = (*env)->FindClass(env, "java/lang/System");
  jmethodID getPropertyMethodId = (*env)->GetStaticMethodID(env, systemClass, "getProperty", "(Ljava/lang/String;)Ljava/lang/String;");

  jstring absolutePropertyName = (*env)->NewStringUTF(env, "faketime.absolute.ms");
  jstring absoluteValueString = (*env)->CallStaticObjectMethod(env, systemClass, getPropertyMethodId, absolutePropertyName);

  if ((*env)->ExceptionCheck(env)) {
    return 0;
  }

  if (absoluteValueString != NULL) {
    const char *absoluteValueStringChars = (*env)->GetStringUTFChars(env, absoluteValueString, NULL);
    jlong time = strtoll(absoluteValueStringChars, &endptr, 10);
    (*env)->ReleaseStringUTFChars(env, absoluteValueString, absoluteValueStringChars);
    return time;
  }

  jstring offsetPropertyName = (*env)->NewStringUTF(env, "faketime.offset.ms");
  jstring offsetValueString = (*env)->CallStaticObjectMethod(env, systemClass, getPropertyMethodId, offsetPropertyName);

  if ((*env)->ExceptionCheck(env)) {
    return 0;
  }

  if (offsetValueString != NULL) {
    const char *offsetValueStringChars = (*env)->GetStringUTFChars(env, offsetValueString, NULL);
    jlong time = realCurrentTimeInMillis(env, jc) + strtoll(offsetValueStringChars, &endptr, 10);
    (*env)->ReleaseStringUTFChars(env, offsetValueString, offsetValueStringChars);
    return time;
  }

  return realCurrentTimeInMillis(env, jc);
}

static void check_jvmti_error(jvmtiEnv *jvmti, jvmtiError errnum, const char *str) {
  if (errnum != JVMTI_ERROR_NONE) {
    char *errnum_str;

    errnum_str = NULL;
    (void)(*jvmti)->GetErrorName(jvmti, errnum, &errnum_str);

    printf("ERROR: JVMTI: %d(%s): %s\n", errnum, (errnum_str==NULL?"Unknown":errnum_str), (str==NULL?"":str));
  }
}

/* Enter a critical section by doing a JVMTI Raw Monitor Enter */
static void enter_critical_section(jvmtiEnv *jvmti) {
  jvmtiError error;

  error = (*jvmti)->RawMonitorEnter(jvmti, gdata->lock);
  check_jvmti_error(jvmti, error, "Cannot enter with raw monitor");
}

/* Exit a critical section by doing a JVMTI Raw Monitor Exit */
static void exit_critical_section(jvmtiEnv *jvmti) {
  jvmtiError error;

  error = (*jvmti)->RawMonitorExit(jvmti, gdata->lock);
  check_jvmti_error(jvmti, error, "Cannot exit with raw monitor");
}

void JNICALL callbackNativeMethodBind(jvmtiEnv *jvmti_env, JNIEnv* jni_env, jthread thread, jmethodID method, void* address, void** new_address_ptr) {
  enter_critical_section(jvmti);

  {
    char *methodName = NULL;
    char *declaringClassName = NULL;
    jclass declaring_class;
    jvmtiError err;

    err = (*jvmti)->GetMethodName(jvmti, method, &methodName, NULL, NULL);

    if (err == JVMTI_ERROR_NONE && strcmp("currentTimeMillis", methodName) == 0) {
      err = (*jvmti)->GetMethodDeclaringClass(jvmti, method, &declaring_class);
      err = (*jvmti)->GetClassSignature(jvmti, declaring_class, &declaringClassName, NULL);

      if (err == JVMTI_ERROR_NONE && strcmp("Ljava/lang/System;", declaringClassName) == 0) {
        if (realCurrentTimeInMillis == NULL) {
          realCurrentTimeInMillis = address;
          *new_address_ptr = (void *) &fakeCurrentTimeInMillis;
        }
      }

      check_jvmti_error(jvmti_env, (*jvmti)->Deallocate(jvmti, (unsigned char *)declaringClassName), "Nope");
    }

    check_jvmti_error(jvmti_env, (*jvmti)->Deallocate(jvmti, (unsigned char *)methodName), "Err");
  }

  exit_critical_section(jvmti);
}

void JNICALL callbackVMInit(jvmtiEnv *jvmti_env, JNIEnv* jni_env, jthread thread) {
  gdata->vm_is_started = JNI_TRUE;
}

JNIEXPORT jint JNICALL Agent_OnLoad(JavaVM *jvm, char *options, void *reserved) {
  static GlobalAgentData data;
  jvmtiEventCallbacks callbacks;
  jint res = (*jvm)->GetEnv(jvm, (void **) &jvmti, JVMTI_VERSION_1_0);

  if (res != JNI_OK || jvmti == NULL) {
    fprintf(stderr, "ERROR: Unable to access JVMTI Version 1");
  }

  (void)memset((void*)&data, 0, sizeof(data));
  gdata = &data;
  gdata->jvmti = jvmti;

  jvmtiCapabilities capabilities;
  memset(&capabilities, 0, sizeof(jvmtiCapabilities));
  capabilities.can_get_owned_monitor_info = 1;
  capabilities.can_generate_native_method_bind_events = 1;
  check_jvmti_error(jvmti, (*jvmti)->AddCapabilities(jvmti, &capabilities), "Unable to get necessary JVMTI capabilities.");

  memset(&callbacks, 0, sizeof(callbacks));
  callbacks.NativeMethodBind = &callbackNativeMethodBind;
  callbacks.VMInit = &callbackVMInit;

  check_jvmti_error(jvmti, (*jvmti)->SetEventCallbacks(jvmti, &callbacks, (jint)sizeof(callbacks)), "Cannot set jvmti callbacks");
  check_jvmti_error(jvmti, (*jvmti)->SetEventNotificationMode(jvmti, JVMTI_ENABLE, JVMTI_EVENT_NATIVE_METHOD_BIND, (jthread)NULL), "Cannot set event notification");
  check_jvmti_error(jvmti, (*jvmti)->SetEventNotificationMode(jvmti, JVMTI_ENABLE, JVMTI_EVENT_VM_INIT, (jthread)NULL), "Cannot set event notification");
  check_jvmti_error(jvmti, (*jvmti)->CreateRawMonitor(jvmti, "agent data", &(gdata->lock)), "Cannot create raw monitor");

  return JNI_OK;
}
