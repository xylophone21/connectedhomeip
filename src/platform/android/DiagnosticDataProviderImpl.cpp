/*
 *
 *    Copyright (c) 2021 Project CHIP Authors
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

/**
 *    @file
 *          Provides an implementation of the DiagnosticDataProvider object
 *          for android platform.
 */

#include <cstddef>
#include <cstring>
#include <jni.h>
#include <platform/internal/CHIPDeviceLayerInternal.h>

#include "DiagnosticDataProviderImpl.h"
#include <lib/support/CHIPJNIError.h>
#include <lib/support/CHIPMem.h>
#include <lib/support/JniTypeWrappers.h>
#include <lib/support/logging/CHIPLogging.h>
#include <platform/DiagnosticDataProvider.h>
#include <unistd.h>

using namespace ::chip::app::Clusters::GeneralDiagnostics;

namespace chip {
namespace DeviceLayer {

DiagnosticDataProviderImpl & DiagnosticDataProviderImpl::GetDefaultInstance()
{
    static DiagnosticDataProviderImpl sInstance;
    return sInstance;
}

void DiagnosticDataProviderImpl::InitializeWithObject(jobject manager)
{
    JNIEnv * env = JniReferences::GetInstance().GetEnvForCurrentThread();
    VerifyOrReturn(env != nullptr,
                   ChipLogError(DeviceLayer, "Failed to GetEnvForCurrentThread for DiagnosticDataProviderManagerImpl"));

    mDiagnosticDataProviderManagerObject = env->NewGlobalRef(manager);
    VerifyOrReturn(mDiagnosticDataProviderManagerObject != nullptr,
                   ChipLogError(DeviceLayer, "Failed to NewGlobalRef DiagnosticDataProviderManager"));

    jclass DiagnosticDataProviderManagerClass = env->GetObjectClass(manager);
    VerifyOrReturn(DiagnosticDataProviderManagerClass != nullptr,
                   ChipLogError(DeviceLayer, "Failed to get DiagnosticDataProviderManager Java class"));

    mGetRebootCountMethod = env->GetMethodID(DiagnosticDataProviderManagerClass, "getRebootCount", "()I");
    if (mGetRebootCountMethod == nullptr)
    {
        ChipLogError(DeviceLayer, "Failed to access DiagnosticDataProviderManager 'getRebootCount' method");
        env->ExceptionClear();
    }

    mGetNifMethod =
        env->GetMethodID(DiagnosticDataProviderManagerClass, "getNetworkInterfaces", "()[Lchip/platform/NetworkInterface;");
    if (mGetNifMethod == nullptr)
    {
        ChipLogError(DeviceLayer, "Failed to access DiagnosticDataProviderManager 'getNetworkInterfaces' method");
        env->ExceptionClear();
    }
}

CHIP_ERROR DiagnosticDataProviderImpl::GetRebootCount(uint16_t & rebootCount)
{
    CHIP_ERROR err = CHIP_NO_ERROR;
    JNIEnv * env   = JniReferences::GetInstance().GetEnvForCurrentThread();
    VerifyOrExit(mDiagnosticDataProviderManagerObject != nullptr, err = CHIP_ERROR_INCORRECT_STATE);
    VerifyOrExit(mGetRebootCountMethod != nullptr, err = CHIP_ERROR_INCORRECT_STATE);
    VerifyOrExit(env != NULL, err = CHIP_JNI_ERROR_NO_ENV);
    ChipLogProgress(DeviceLayer, "Received GetRebootCount");

    {
        jint count = env->CallIntMethod(mDiagnosticDataProviderManagerObject, mGetRebootCountMethod);
        if (count > UINT16_MAX)
        {
            return CHIP_ERROR_INVALID_INTEGER_VALUE;
        }
        rebootCount = static_cast<uint16_t>(count);
    }

exit:
    if (err != CHIP_NO_ERROR)
    {
        ChipLogError(Zcl, "ChannelManager::getChannelList status error: %s", err.AsString());
    }

    return err;
}

CHIP_ERROR DiagnosticDataProviderImpl::GetNetworkInterfaces(NetworkInterface ** netifpp)
{
    CHIP_ERROR err = CHIP_NO_ERROR;
    JNIEnv * env   = JniReferences::GetInstance().GetEnvForCurrentThread();
    VerifyOrExit(mDiagnosticDataProviderManagerObject != nullptr, err = CHIP_ERROR_INCORRECT_STATE);
    VerifyOrExit(mGetNifMethod != nullptr, err = CHIP_ERROR_INCORRECT_STATE);
    VerifyOrExit(env != NULL, err = CHIP_JNI_ERROR_NO_ENV);
    {
        ChipLogProgress(DeviceLayer, "Received GetNetworkInterfaces");
        jobjectArray nifList = (jobjectArray) env->CallObjectMethod(mDiagnosticDataProviderManagerObject, mGetNifMethod);
        if (env->ExceptionCheck())
        {
            ChipLogError(DeviceLayer, "Java exception in DiagnosticDataProviderImpl::GetNetworkInterfaces");
            env->ExceptionDescribe();
            env->ExceptionClear();
            return CHIP_ERROR_INCORRECT_STATE;
        }
        jint length = env->GetArrayLength(nifList);

        NetworkInterface * head = nullptr;
        for (jint i = 0; i < length; i++)
        {
            NetworkInterface * ifp = new NetworkInterface();

            jobject nifObject = env->GetObjectArrayElement(nifList, i);
            jclass nifClass   = env->GetObjectClass(nifObject);

            jfieldID getNameField = env->GetFieldID(nifClass, "name", "Ljava/lang/String;");
            jstring jname         = static_cast<jstring>(env->GetObjectField(nifObject, getNameField));
            if (jname != NULL)
            {
                JniUtfString name(env, jname);
                strncpy(ifp->Name, name.c_str(), Inet::InterfaceId::kMaxIfNameLength);
                ifp->Name[Inet::InterfaceId::kMaxIfNameLength - 1] = '\0';
                ifp->name                                          = CharSpan(ifp->Name, strlen(ifp->Name));
            }

            jfieldID isOperationalField = env->GetFieldID(nifClass, "isOperational", "Z");
            ifp->isOperational          = static_cast<bool>(env->GetBooleanField(nifObject, isOperationalField));

            jfieldID getOpsrIPV4Field = env->GetFieldID(nifClass, "offPremiseServicesReachableIPv4", "I");
            jint jOpsrIPV4            = env->GetIntField(nifObject, getOpsrIPV4Field);
            switch (jOpsrIPV4)
            {
            case offPremiseServicesReachableUnknown:
                ifp->offPremiseServicesReachableIPv4.SetNull();
                break;
            case offPremiseServicesReachableYes:
                ifp->offPremiseServicesReachableIPv4.SetNonNull(true);
                break;
            case offPremiseServicesReachableNo:
                ifp->offPremiseServicesReachableIPv4.SetNonNull(false);
                break;
            }

            jfieldID getOpsrIPV6Field = env->GetFieldID(nifClass, "offPremiseServicesReachableIPv6", "I");
            jint jOpsrIPV6            = env->GetIntField(nifObject, getOpsrIPV6Field);
            switch (jOpsrIPV6)
            {
            case offPremiseServicesReachableUnknown:
                ifp->offPremiseServicesReachableIPv6.SetNull();
                break;
            case offPremiseServicesReachableYes:
                ifp->offPremiseServicesReachableIPv6.SetNonNull(true);
                break;
            case offPremiseServicesReachableNo:
                ifp->offPremiseServicesReachableIPv6.SetNonNull(false);
                break;
            }

            jfieldID gethardwareAddressField = env->GetFieldID(nifClass, "hardwareAddress", "[B");
            jobject jHardwareAddressObj      = env->GetObjectField(nifObject, gethardwareAddressField);
            if (jHardwareAddressObj != NULL)
            {
                jbyteArray arr = reinterpret_cast<jbyteArray>(jHardwareAddressObj);
                size_t len     = env->GetArrayLength(arr);
                len            = (len > kMaxHardwareAddrSize) ? kMaxHardwareAddrSize : len;
                env->GetByteArrayRegion(arr, 0, len, reinterpret_cast<jbyte *>(ifp->MacAddress));
                ifp->hardwareAddress = ByteSpan(ifp->MacAddress, 6);
            }

            jfieldID getTypeField = env->GetFieldID(nifClass, "type", "I");
            ifp->type             = static_cast<InterfaceType>(env->GetIntField(nifObject, getTypeField));

            ifp->Next = head;
            head      = ifp;
        }
        *netifpp = head;
    }

exit:
    if (err != CHIP_NO_ERROR)
    {
        ChipLogError(Zcl, "ChannelManager::getChannelList status error: %s", err.AsString());
    }
    return err;
}

void DiagnosticDataProviderImpl::ReleaseNetworkInterfaces(NetworkInterface * netifp)
{
    while (netifp)
    {
        NetworkInterface * del = netifp;
        netifp                 = netifp->Next;
        delete del;
    }
}

} // namespace DeviceLayer
} // namespace chip
