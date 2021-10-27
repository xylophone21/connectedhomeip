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

#include <iostream>
#include <thread>
#include <platform/CHIPDeviceLayer.h>
#include <platform/PlatformManager.h>
#include <app/server/OnboardingCodesUtil.h>
#include <app/server/Server.h>
#include <lib/core/CHIPError.h>
#include <setup_payload/QRCodeSetupPayloadGenerator.h>
#include <setup_payload/SetupPayload.h>
#include <lib/support/CHIPMem.h>
#include <lib/support/ScopedBuffer.h>
#include <lib/support/JniTypeWrappers.h>
#include <credentials/DeviceAttestationCredsProvider.h>
#include <credentials/examples/DeviceAttestationCredsExample.h>




constexpr char kQrCodeBaseUrl[]                   = "https://dhrishi.github.io/connectedhomeip/qrcode.html";
constexpr char kUrlDataAssignmentPhrase[]         = "?data=";
static jobject sgetQRcodeObject = nullptr;
static jclass sgetQRcodeClass = nullptr;

using namespace chip;
using namespace chip::Credentials;
using namespace chip::Inet;
using namespace chip::Transport;
using namespace chip::DeviceLayer;


namespace {
void EventHandler(const chip::DeviceLayer::ChipDeviceEvent * event, intptr_t arg)
{
    (void) arg;
    if (event->Type == chip::DeviceLayer::DeviceEventType::kCHIPoBLEConnectionEstablished)
    {
        ChipLogProgress(DeviceLayer, "Receive kCHIPoBLEConnectionEstablished");
    }
}
} // namespace
void callBackQrCode(chip::RendezvousInformationFlags aRendezvousFlags);
void PrintOnboardingCodesInAppMain(chip::RendezvousInformationFlags aRendezvousFlags);

int ChipLinuxAppInit(int argc, char ** argv)
{
    CHIP_ERROR err = CHIP_NO_ERROR;

    err = chip::Platform::MemoryInit();
    SuccessOrExit(err);

    err = chip::DeviceLayer::PlatformMgr().InitChipStack();
    SuccessOrExit(err);

    ConfigurationMgr().LogDeviceConfig();
#ifdef CONFIG_RENDEZVOUS_MODE
    PrintOnboardingCodesInAppMain(static_cast<chip::RendezvousInformationFlags>(CONFIG_RENDEZVOUS_MODE));
#else
    PrintOnboardingCodesInAppMain(chip::RendezvousInformationFlag::kOnNetwork);
#endif

    // TODO: move load DAC to java
    SetDeviceAttestationCredentialsProvider(Examples::GetExampleDACProvider());

    chip::DeviceLayer::PlatformMgrImpl().AddEventHandler(EventHandler, 0);

    // Init ZCL Data Model and CHIP App Server
    chip::Server::GetInstance().Init(nullptr, CHIP_PORT, CHIP_UDC_PORT);

exit:
    if (err != CHIP_NO_ERROR)
    {
        ChipLogProgress(NotSpecified, "Failed to run Linux Lighting App: %s ", ErrorStr(err));
        // End the program with non zero error code to indicate a error.
        return 1;
    }
    return 0;
}

void ChipLinuxAppMainLoop()
{
    chip::DeviceLayer::PlatformMgr().RunEventLoop();
}

void callBackQrCode(std::string QRCode,const char* methodName)
{

    JNIEnv * env = JniReferences::GetInstance().GetEnvForCurrentThread();

    sgetQRcodeClass = env->GetObjectClass(sgetQRcodeObject);
    VerifyOrReturn(sgetQRcodeClass != nullptr, ChipLogError(DeviceLayer, "Failed 111 to get Java class"));
    jmethodID mGetMethod = env->GetMethodID(sgetQRcodeClass, methodName, "(Ljava/lang/String;)V");
    if (mGetMethod == nullptr)
    {
        ChipLogError(DeviceLayer, "Failed to access KVS 'get' method");
        env->ExceptionClear();
    }
    env->CallVoidMethod(sgetQRcodeObject,mGetMethod,env->NewStringUTF(QRCode.c_str()));
}

void PrintOnboardingCodesInAppMain(chip::RendezvousInformationFlags aRendezvousFlags)
{
    std::string QRCode;
    std::string manualPairingCode;

    if (GetQRCode(QRCode, aRendezvousFlags) == CHIP_NO_ERROR)
    {
        chip::Platform::ScopedMemoryBuffer<char> qrCodeBuffer;
        const size_t qrCodeBufferMaxSize = strlen(kQrCodeBaseUrl) + strlen(kUrlDataAssignmentPhrase) + 3 * QRCode.size() + 1;
        qrCodeBuffer.Alloc(qrCodeBufferMaxSize);

        ChipLogProgress(AppServer, "SetupQRCode: [%s]", QRCode.c_str());
        if (GetQRCodeUrl(&qrCodeBuffer[0], qrCodeBufferMaxSize, QRCode) == CHIP_NO_ERROR)
        {
            ChipLogProgress(AppServer, "Copy/paste the below URL in a browser to see the QR Code:");
            ChipLogProgress(AppServer, "%s", &qrCodeBuffer[0]);
        }
        callBackQrCode(QRCode,"onQrCode");
    }
    else
    {
        ChipLogError(AppServer, "Getting QR code failed!");
    }

    if (GetManualPairingCode(manualPairingCode, aRendezvousFlags) == CHIP_NO_ERROR)
    {
        ChipLogProgress(AppServer, "Manual pairing code: [%s]", manualPairingCode.c_str());
        callBackQrCode(manualPairingCode,"onManualPairingCode");
    }
    else
    {
        ChipLogError(AppServer, "Getting manual pairing code failed!");
    }
}


void  setQRcodeobject(jobject QRcodeObject)
{
    JNIEnv * env                     = JniReferences::GetInstance().GetEnvForCurrentThread();
    sgetQRcodeObject      = env->NewGlobalRef(QRcodeObject);
 //   sgetQRcodeClass = env->GetObjectClass(sgetQRcodeObject);
    VerifyOrReturn(sgetQRcodeObject != nullptr, ChipLogError(DeviceLayer, "Failed to get Java object"));
}
