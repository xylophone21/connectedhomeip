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

static void * IOThreadAppMain(void * arg);

JavaVM * sJVM;
pthread_t sIOThread = 0;





jint JNI_OnLoad(JavaVM * jvm, void * reserved)
{
	
    CHIP_ERROR err = CHIP_NO_ERROR;
    JNIEnv * env;

    chip::Platform::MemoryInit();

    // Save a reference to the JVM.  Will need this to call back into Java.
    JniReferences::GetInstance().SetJavaVm(jvm, "chip/appserver/ChipAppServer");
    sJVM = jvm;

    // Get a JNI environment object.
    env = JniReferences::GetInstance().GetEnvForCurrentThread();


    ChipLogProgress(AppServer, "Loading Java class references.");

    err= AndroidChipPlatformJNI_OnLoad(jvm, reserved);

    return (err == CHIP_NO_ERROR) ? JNI_VERSION_1_6 : JNI_ERR;
    	
}

void JNI_OnUnload(JavaVM * jvm, void * reserved)
{
	
    ChipLogProgress(DeviceLayer, "AndroidChipPlatform JNI_OnUnload() called");
    chip::Platform::MemoryShutdown();
}



JNI_METHOD(jint, entryAppmain)(JNIEnv * env, jobject self)
{
    chip::DeviceLayer::StackLock lock;
  //  CHIP_ERROR err                           = CHIP_NO_ERROR;

 //   err = DeviceLayer::PlatformMgr().InitChipStack();
    DeviceLayer::PlatformMgr().InitChipStack();

    int argc=0;
    char * argv[]={0};
    ChipLinuxAppInit(argc, argv);

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
    attachArgs.name    = (char *) "CHIP Device Controller IO Thread";
    attachArgs.group   = NULL;
#ifdef __ANDROID__
    sJVM->AttachCurrentThreadAsDaemon(&env, (void *) &attachArgs);
#else
    sJVM->AttachCurrentThreadAsDaemon((void **) &env, (void *) &attachArgs);
#endif

    ChipLinuxAppMainLoop();
    
    // Detach the thread from the JVM.
    sJVM->DetachCurrentThread();

    return NULL;
}




JNI_METHOD(void, setConfigurationManager)(JNIEnv * env, jclass self, jobject config)
{
    chip::DeviceLayer::StackLock lock;
    chip::DeviceLayer::ConfigurationMgrImpl().InitializeWithObject(config);
}


JNI_METHOD(void, setQRCodeListener)(JNIEnv * env, jclass self, jobject listener)
{
    chip::DeviceLayer::StackLock lock;
    setQRcodeobject(listener);
}
