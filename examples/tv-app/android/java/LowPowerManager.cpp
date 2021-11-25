/*
 *
 *    Copyright (c) 2021 Project CHIP Authors
 *    All rights reserved.
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

#include "LowPowerManager.h"
#include <lib/support/CHIPJNIError.h>
#include <lib/support/JniReferences.h>
#include <lib/support/JniTypeWrappers.h>
#include <lib/support/logging/CHIPLogging.h>
#include <lib/support/CodeUtils.h>


using namespace chip;

LowPowerManager LowPowerManager::sInstance;

bool lowPowerClusterSleep()
{
    return LowPowerMgr().Sleep();
}

void LowPowerManager::InitializeWithObjects(jobject managerObject)
{
    JNIEnv * env = JniReferences::GetInstance().GetEnvForCurrentThread();
    VerifyOrReturn(env != nullptr, ChipLogError(Zcl, "Failed to GetEnvForCurrentThread for LowPowerManager"));

    mLowPowerManagerObject  = env->NewGlobalRef(managerObject);
    VerifyOrReturn(mLowPowerManagerObject != nullptr, ChipLogError(Zcl, "Failed to NewGlobalRef LowPowerManager"));

    jclass LowPowerManagerClass = env->GetObjectClass(managerObject);
    VerifyOrReturn(LowPowerManagerClass != nullptr, ChipLogError(Zcl, "Failed to get LowPowerManager Java class"));

    mSleepMethod = env->GetMethodID(LowPowerManagerClass, "sleep", "()Z");
    if (mSleepMethod == nullptr)
    {
        ChipLogError(Zcl, "Failed to access LowPowerManager 'sleep' method");
        env->ExceptionClear();
    }
}

bool LowPowerManager::Sleep()
{
    jboolean ret = JNI_FALSE;
    JNIEnv * env   = JniReferences::GetInstance().GetEnvForCurrentThread();

    ChipLogProgress(Zcl, "Received LowPowerManager::Sleep");
    VerifyOrExit(mLowPowerManagerObject != nullptr, ChipLogError(Zcl, "mLowPowerManagerObject null"));
    VerifyOrExit(mSleepMethod != nullptr, ChipLogError(Zcl, "mSleepMethod null"));
    VerifyOrExit(env != NULL, ChipLogError(Zcl, "env null"));

    env->ExceptionClear();
    ret = env->CallBooleanMethod(mLowPowerManagerObject, mSleepMethod);
    if (env->ExceptionCheck())
    {
        ChipLogError(DeviceLayer, "Java exception in LowPowerManager::Sleep");
        env->ExceptionDescribe();
        env->ExceptionClear();
        return false;
    }

exit:
    return static_cast<bool>(ret);
}
