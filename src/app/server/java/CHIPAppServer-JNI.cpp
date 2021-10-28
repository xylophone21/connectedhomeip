/*
 *   Copyright (c) 2021 Project CHIP Authors
 *   All rights reserved.
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 *
 */

/**
 *    @file
 *      Implementation of JNI bridge for CHIP App Server for Android TV apps
 *
 */
#include <lib/core/CHIPError.h>
#include <lib/support/CHIPJNIError.h>
#include <lib/support/CHIPMem.h>
#include <lib/support/CodeUtils.h>
#include <lib/support/JniReferences.h>
#include <lib/support/JniTypeWrappers.h>
#include <platform/CHIPDeviceConfig.h>
#include <platform/ConfigurationManager.h>
#include <platform/ConnectivityManager.h>
#include <platform/KeyValueStoreManager.h>
#include <platform/internal/BLEManager.h>
#include <platform/android/AndroidChipPlatform-JNI.h>
#include "AppMain.h"

using namespace chip;
using namespace chip::DeviceLayer;


#define JNI_METHOD(RETURN, METHOD_NAME)                                                                                            \
    extern "C" JNIEXPORT RETURN JNICALL Java_chip_appserver_ChipAppServer_##METHOD_NAME

#ifndef PTHREAD_NULL
#define PTHREAD_NULL 0
#endif // PTHREAD_NULL

static void ThrowError(JNIEnv * env, CHIP_ERROR errToThrow);
static void * IOThreadAppMain(void * arg);
static CHIP_ERROR N2J_Error(JNIEnv * env, CHIP_ERROR inErr, jthrowable & outEx);

namespace {
JavaVM * sJVM;
pthread_t sIOThread = PTHREAD_NULL;
jclass sChipAppServerExceptionCls = NULL;
} // namespace

jint JNI_OnLoad(JavaVM * jvm, void * reserved)
{
    CHIP_ERROR err = CHIP_NO_ERROR;
    JNIEnv * env;

    ChipLogProgress(AppServer, "JNI_OnLoad() called");

    chip::Platform::MemoryInit();

    // Save a reference to the JVM.  Will need this to call back into Java.
    JniReferences::GetInstance().SetJavaVm(jvm, "chip/appserver/ChipAppServer");
    sJVM = jvm;

    // Get a JNI environment object.
    env = JniReferences::GetInstance().GetEnvForCurrentThread();
    VerifyOrExit(env != NULL, err = CHIP_JNI_ERROR_NO_ENV);

    ChipLogProgress(AppServer, "Loading Java class references.");

    // Get various class references need by the API.
    err = JniReferences::GetInstance().GetClassRef(env, "chip/appserver/ChipAppServerException",
                                                   sChipAppServerExceptionCls);
    SuccessOrExit(err);
    ChipLogProgress(AppServer, "Java class references loaded.");

    err = AndroidChipPlatformJNI_OnLoad(jvm, reserved);
    SuccessOrExit(err);

exit:
    if (err != CHIP_NO_ERROR)
    {
        ThrowError(env, err);
        chip::DeviceLayer::StackUnlock unlock;
        JNI_OnUnload(jvm, reserved);
    }

    return (err == CHIP_NO_ERROR) ? JNI_VERSION_1_6 : JNI_ERR;
}

void JNI_OnUnload(JavaVM * jvm, void * reserved)
{
    chip::DeviceLayer::StackLock lock;
    ChipLogProgress(AppServer, "JNI_OnUnload() called");

    // If the IO thread has been started, shut it down and wait for it to exit.
    if (sIOThread != PTHREAD_NULL)
    {
        chip::DeviceLayer::PlatformMgr().StopEventLoopTask();

        chip::DeviceLayer::StackUnlock unlock;
        pthread_join(sIOThread, NULL);
    }

    sJVM = NULL;

    chip::Platform::MemoryShutdown();
}

JNI_METHOD(jint, startApp)(JNIEnv * env, jobject self)
{
    chip::DeviceLayer::StackLock lock;

    ChipAndroidAppInit();

    if (sIOThread == PTHREAD_NULL)
    {
	    pthread_create(&sIOThread, NULL, IOThreadAppMain, NULL);
    }

    return JNI_VERSION_1_6;
}

void * IOThreadAppMain(void * arg)
{
    JNIEnv * env;
    JavaVMAttachArgs attachArgs;

    // Attach the IO thread to the JVM as a daemon thread.
    // This allows the JVM to shutdown without waiting for this thread to exit.
    attachArgs.version = JNI_VERSION_1_6;
    attachArgs.name    = (char *) "CHIP AppServer IO Thread";
    attachArgs.group   = NULL;
#ifdef __ANDROID__
    sJVM->AttachCurrentThreadAsDaemon(&env, (void *) &attachArgs);
#else
    sJVM->AttachCurrentThreadAsDaemon((void **) &env, (void *) &attachArgs);
#endif

    ChipLogProgress(AppServer, "IO thread starting");
    chip::DeviceLayer::PlatformMgr().RunEventLoop();
    ChipLogProgress(AppServer, "IO thread ending");

    // Detach the thread from the JVM.
    sJVM->DetachCurrentThread();

    return NULL;
}

void ThrowError(JNIEnv * env, CHIP_ERROR errToThrow)
{
    CHIP_ERROR err = CHIP_NO_ERROR;
    jthrowable ex;

    err = N2J_Error(env, errToThrow, ex);
    if (err == CHIP_NO_ERROR)
    {
        env->Throw(ex);
    }
}

CHIP_ERROR N2J_Error(JNIEnv * env, CHIP_ERROR inErr, jthrowable & outEx)
{
    CHIP_ERROR err      = CHIP_NO_ERROR;
    const char * errStr = NULL;
    jstring errStrObj   = NULL;
    jmethodID constructor;

    env->ExceptionClear();
    constructor = env->GetMethodID(sChipAppServerExceptionCls, "<init>", "(ILjava/lang/String;)V");
    VerifyOrExit(constructor != NULL, err = CHIP_JNI_ERROR_METHOD_NOT_FOUND);

    switch (inErr.AsInteger())
    {
    case CHIP_JNI_ERROR_TYPE_NOT_FOUND.AsInteger():
        errStr = "CHIP App Server Error: JNI type not found";
        break;
    case CHIP_JNI_ERROR_METHOD_NOT_FOUND.AsInteger():
        errStr = "CHIP App Server Error: JNI method not found";
        break;
    case CHIP_JNI_ERROR_FIELD_NOT_FOUND.AsInteger():
        errStr = "CHIP App Server Error: JNI field not found";
        break;
    case CHIP_JNI_ERROR_DEVICE_NOT_FOUND.AsInteger():
        errStr = "CHIP App Server Error: Device not found";
        break;
    default:
        errStr = ErrorStr(inErr);
        break;
    }
    errStrObj = (errStr != NULL) ? env->NewStringUTF(errStr) : NULL;

    outEx = (jthrowable) env->NewObject(sChipAppServerExceptionCls, constructor, static_cast<jint>(inErr.AsInteger()),
                                        errStrObj);
    VerifyOrExit(!env->ExceptionCheck(), err = CHIP_JNI_ERROR_EXCEPTION_THROWN);

exit:
    env->DeleteLocalRef(errStrObj);
    return err;
}
