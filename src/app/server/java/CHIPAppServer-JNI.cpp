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
 *      Implementation of JNI bridge for CHIP App Server for Android apps
 *
 */
#include <lib/support/CHIPJNIError.h>
#include <lib/support/JniReferences.h>
#include <lib/support/JniTypeWrappers.h>

#include <app/chip-zcl-zpro-codec.h>
#include <atomic>
#include <ble/BleUUID.h>
#include <controller/CHIPDeviceController.h>
#include <jni.h>
#include <lib/support/CHIPMem.h>
#include <lib/support/CodeUtils.h>
#include <lib/support/ErrorStr.h>
#include <lib/support/SafeInt.h>
#include <lib/support/ThreadOperationalDataset.h>
#include <lib/support/logging/CHIPLogging.h>
#include <platform/KeyValueStoreManager.h>
#include <protocols/Protocols.h>
#include <protocols/temp_zcl/TempZCL.h>
#include <pthread.h>

#include <platform/android/AndroidChipPlatform-JNI.h>

using namespace chip;
using namespace chip::Inet;
using namespace chip::Controller;

#define JNI_METHOD(RETURN, METHOD_NAME)                                                                                            \
    extern "C" JNIEXPORT RETURN JNICALL Java_chip_devicecontroller_ChipDeviceController_##METHOD_NAME

namespace {
// JavaVM * sJVM;
} // namespace

jint JNI_OnLoad(JavaVM * jvm, void * reserved)
{
    return JNI_VERSION_1_6;
}

void JNI_OnUnload(JavaVM * jvm, void * reserved)
{
}