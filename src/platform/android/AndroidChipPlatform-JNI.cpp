/*
 *   Copyright (c) 2020-2021 Project CHIP Authors
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
 *      Implementation of JNI bridge for CHIP Device Controller for Android apps
 *
 */
#include <core/CHIPError.h>
#include <support/JniTypeWrappers.h>
#include <support/CodeUtils.h>
#include <support/JniReferences.h>
#include <support/CHIPJNIError.h>
#include <support/StackLock.h>
#include <platform/ConnectivityManager.h>
#include <platform/internal/BLEManager.h>
#include <support/CHIPMem.h>

#include "BLEManagerImpl.h"

using namespace chip;

#define JNI_METHOD(RETURN, METHOD_NAME)                                                                                            \
    extern "C" JNIEXPORT RETURN JNICALL Java_chip_platform_AndroidChipPlatform_##METHOD_NAME

static void ThrowError(JNIEnv * env, CHIP_ERROR errToThrow);
static CHIP_ERROR N2J_Error(JNIEnv * env, CHIP_ERROR inErr, jthrowable & outEx);

namespace {
    JavaVM * sJVM;
    jclass sAndroidChipPlatformCls = NULL;
    jclass sAndroidChipPlatformExceptionCls = NULL;
} // namespace

jint JNI_OnLoad(JavaVM * jvm, void * reserved)
{
    CHIP_ERROR err = CHIP_NO_ERROR;
    JNIEnv * env;

    ChipLogProgress(DeviceLayer, "AndroidChipPlatform JNI_OnLoad() called");

    chip::Platform::MemoryInit();

    // Save a reference to the JVM.  Will need this to call back into Java.
    JniReferences::GetInstance().SetJavaVm(jvm, "chip/platform/AndroidChipPlatform");
    sJVM = jvm;

    // Get a JNI environment object.
    env = JniReferences::GetInstance().GetEnvForCurrentThread();
    VerifyOrExit(env != NULL, err = CHIP_JNI_ERROR_NO_ENV);

    ChipLogProgress(DeviceLayer, "Loading Java class references.");

    // Get various class references need by the API.
    err = JniReferences::GetInstance().GetClassRef(env, "chip/platform/AndroidChipPlatform", sAndroidChipPlatformCls);
    SuccessOrExit(err);
    err = JniReferences::GetInstance().GetClassRef(env, "chip/platform/AndroidChipPlatformException",
                                                   sAndroidChipPlatformExceptionCls);
    SuccessOrExit(err);
    ChipLogProgress(DeviceLayer, "Java class references loaded.");

exit:
    if (err != CHIP_NO_ERROR)
    {
        ThrowError(env, err);
        StackUnlockGuard unlockGuard(JniReferences::GetInstance().GetStackLock());
        JNI_OnUnload(jvm, reserved);
    }

    return (err == CHIP_NO_ERROR) ? JNI_VERSION_1_6 : JNI_ERR;
}

void JNI_OnUnload(JavaVM * jvm, void * reserved)
{
    StackLockGuard lock(JniReferences::GetInstance().GetStackLock());
    ChipLogProgress(DeviceLayer, "AndroidChipPlatform JNI_OnUnload() called");

    chip::Platform::MemoryShutdown();
}

JNI_METHOD(void,setBLEManagerImpl)(JNIEnv *, jobject manager) 
{
    StackLockGuard lock(JniReferences::GetInstance().GetStackLock());
    chip::DeviceLayer::Internal::BLEMgrImpl().InitializeWithObject(manager);
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
    constructor = env->GetMethodID(sAndroidChipPlatformExceptionCls, "<init>", "(ILjava/lang/String;)V");
    VerifyOrExit(constructor != NULL, err = CHIP_JNI_ERROR_METHOD_NOT_FOUND);

    switch (inErr.AsInteger())
    {
    case CHIP_JNI_ERROR_TYPE_NOT_FOUND.AsInteger():
        errStr = "CHIP Device Controller Error: JNI type not found";
        break;
    case CHIP_JNI_ERROR_METHOD_NOT_FOUND.AsInteger():
        errStr = "CHIP Device Controller Error: JNI method not found";
        break;
    case CHIP_JNI_ERROR_FIELD_NOT_FOUND.AsInteger():
        errStr = "CHIP Device Controller Error: JNI field not found";
        break;
    case CHIP_JNI_ERROR_DEVICE_NOT_FOUND.AsInteger():
        errStr = "CHIP Device Controller Error: Device not found";
        break;
    default:
        errStr = ErrorStr(inErr);
        break;
    }
    errStrObj = (errStr != NULL) ? env->NewStringUTF(errStr) : NULL;

    outEx = (jthrowable) env->NewObject(sAndroidChipPlatformExceptionCls, constructor, static_cast<jint>(inErr.AsInteger()),
                                        errStrObj);
    VerifyOrExit(!env->ExceptionCheck(), err = CHIP_JNI_ERROR_EXCEPTION_THROWN);

exit:
    env->DeleteLocalRef(errStrObj);
    return err;
}
