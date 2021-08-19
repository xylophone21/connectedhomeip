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
 *      Implementation of JNI bridge for CHIP Test for Android apps
 *
 */

#include <jni.h>

#include <core/CHIPError.h>
#include <support/CodeUtils.h>

#include <support/JniReferences.h>
#include <support/CHIPJNIError.h>
#include <support/StackLock.h>

using namespace chip;

namespace {
    JavaVM * sJVM;
    jclass sTestEngineCls = NULL;
    jclass sTestEngineExceptionCls = NULL;
} // namespace

static void ThrowError(JNIEnv * env, CHIP_ERROR errToThrow);
static CHIP_ERROR N2J_Error(JNIEnv * env, CHIP_ERROR inErr, jthrowable & outEx);
// static void ReportError(JNIEnv * env, CHIP_ERROR cbErr, const char * functName);

jint JNI_OnLoad(JavaVM * jvm, void * reserved)
{
    CHIP_ERROR err = CHIP_NO_ERROR;
    JNIEnv * env;

    ChipLogProgress(Test, "JNI_OnLoad() called");

    // Save a reference to the JVM.  Will need this to call back into Java.
    JniReferences::GetInstance().SetJavaVm(jvm, "chip/test/TestEngine");
    sJVM = jvm;

    // Get a JNI environment object.
    env = JniReferences::GetInstance().GetEnvForCurrentThread();
    VerifyOrExit(env != NULL, err = CHIP_JNI_ERROR_NO_ENV);

    ChipLogProgress(Controller, "Loading Java class references.");

    // Get various class references need by the API.
    err = JniReferences::GetInstance().GetClassRef(env, "chip/test/TestEngine", sTestEngineCls);
    SuccessOrExit(err);

    err = JniReferences::GetInstance().GetClassRef(env, "chip/test/TestEngineException",
                                                   sTestEngineExceptionCls);
    SuccessOrExit(err);
    ChipLogProgress(Controller, "Java class references loaded.");

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
    ChipLogProgress(Controller, "JNI_OnUnload() called");

    sJVM = NULL;
}


// void ReportError(JNIEnv * env, CHIP_ERROR cbErr, const char * functName)
// {
//     if (cbErr == CHIP_JNI_ERROR_EXCEPTION_THROWN)
//     {
//         ChipLogError(Controller, "Java exception thrown in %s", functName);
//         env->ExceptionDescribe();
//     }
//     else
//     {
//         const char * errStr;
//         switch (cbErr.AsInteger())
//         {
//         case CHIP_JNI_ERROR_TYPE_NOT_FOUND.AsInteger():
//             errStr = "JNI type not found";
//             break;
//         case CHIP_JNI_ERROR_METHOD_NOT_FOUND.AsInteger():
//             errStr = "JNI method not found";
//             break;
//         case CHIP_JNI_ERROR_FIELD_NOT_FOUND.AsInteger():
//             errStr = "JNI field not found";
//             break;
//         default:
//             errStr = ErrorStr(cbErr);
//             break;
//         }
//         ChipLogError(Controller, "Error in %s : %s", functName, errStr);
//     }
// }

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
    constructor = env->GetMethodID(sTestEngineExceptionCls, "<init>", "(ILjava/lang/String;)V");
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

    outEx = (jthrowable) env->NewObject(sTestEngineExceptionCls, constructor, static_cast<jint>(inErr.AsInteger()),
                                        errStrObj);
    VerifyOrExit(!env->ExceptionCheck(), err = CHIP_JNI_ERROR_EXCEPTION_THROWN);

exit:
    env->DeleteLocalRef(errStrObj);
    return err;
}

extern "C"
JNIEXPORT jint JNICALL
Java_chip_test_TestEngine_nativeRunTest(JNIEnv *env, jclass clazz, jstring testFile) {
    // TODO: implement runTest()
    return 0;
}