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

// THIS FILE IS GENERATED BY ZAP

#pragma once

#include <app-common/zap-generated/af-structs.h>
#include <app/Command.h>
#include <app/InteractionModelEngine.h>
#include <app/util/af-enums.h>
#include <app/util/attribute-filter.h>
#include <app/util/im-client-callbacks.h>
#include <inttypes.h>
#include <lib/support/FunctionTraits.h>
#include <lib/support/Span.h>

// Note: The IMDefaultResponseCallback is a bridge to the old CallbackMgr before IM is landed, so it still accepts EmberAfStatus
// instead of IM status code.
// #6308 should handle IM error code on the application side, either modify this function or remove this.
typedef void (*ReadReportingConfigurationReportedCallback)(void * context, uint16_t minInterval, uint16_t maxInterval);
typedef void (*ReadReportingConfigurationReceivedCallback)(void * context, uint16_t timeout);

// Cluster Specific Response Callbacks
typedef void (*GeneralCommissioningClusterArmFailSafeResponseCallback)(void * context, uint8_t errorCode, uint8_t * debugText);
typedef void (*GeneralCommissioningClusterCommissioningCompleteResponseCallback)(void * context, uint8_t errorCode,
                                                                                 uint8_t * debugText);
typedef void (*GeneralCommissioningClusterSetRegulatoryConfigResponseCallback)(void * context, uint8_t errorCode,
                                                                               uint8_t * debugText);
typedef void (*NetworkCommissioningClusterAddThreadNetworkResponseCallback)(void * context, uint8_t errorCode, uint8_t * debugText);
typedef void (*NetworkCommissioningClusterAddWiFiNetworkResponseCallback)(void * context, uint8_t errorCode, uint8_t * debugText);
typedef void (*NetworkCommissioningClusterDisableNetworkResponseCallback)(void * context, uint8_t errorCode, uint8_t * debugText);
typedef void (*NetworkCommissioningClusterEnableNetworkResponseCallback)(void * context, uint8_t errorCode, uint8_t * debugText);
typedef void (*NetworkCommissioningClusterRemoveNetworkResponseCallback)(void * context, uint8_t errorCode, uint8_t * debugText);
typedef void (*NetworkCommissioningClusterScanNetworksResponseCallback)(
    void * context, uint8_t errorCode, uint8_t * debugText, /* TYPE WARNING: array array defaults to */ uint8_t * wifiScanResults,
    /* TYPE WARNING: array array defaults to */ uint8_t * threadScanResults);
typedef void (*NetworkCommissioningClusterUpdateThreadNetworkResponseCallback)(void * context, uint8_t errorCode,
                                                                               uint8_t * debugText);
typedef void (*NetworkCommissioningClusterUpdateWiFiNetworkResponseCallback)(void * context, uint8_t errorCode,
                                                                             uint8_t * debugText);
typedef void (*OperationalCredentialsClusterNOCResponseCallback)(void * context, uint8_t StatusCode, uint8_t FabricIndex,
                                                                 chip::ByteSpan DebugText);
typedef void (*OperationalCredentialsClusterOpCSRResponseCallback)(void * context, chip::ByteSpan NOCSRElements,
                                                                   chip::ByteSpan AttestationSignature);

// List specific responses
void GeneralCommissioningClusterBasicCommissioningInfoListListAttributeFilter(chip::TLV::TLVReader * data,
                                                                              chip::Callback::Cancelable * onSuccessCallback,
                                                                              chip::Callback::Cancelable * onFailureCallback);
typedef void (*GeneralCommissioningBasicCommissioningInfoListListAttributeCallback)(void * context, uint16_t count,
                                                                                    _BasicCommissioningInfoType * entries);
void OperationalCredentialsClusterFabricsListListAttributeFilter(chip::TLV::TLVReader * data,
                                                                 chip::Callback::Cancelable * onSuccessCallback,
                                                                 chip::Callback::Cancelable * onFailureCallback);
typedef void (*OperationalCredentialsFabricsListListAttributeCallback)(void * context, uint16_t count, _FabricDescriptor * entries);
void OperationalCredentialsClusterTrustedRootCertificatesListAttributeFilter(chip::TLV::TLVReader * data,
                                                                             chip::Callback::Cancelable * onSuccessCallback,
                                                                             chip::Callback::Cancelable * onFailureCallback);
typedef void (*OperationalCredentialsTrustedRootCertificatesListAttributeCallback)(void * context, uint16_t count,
                                                                                   chip::ByteSpan * entries);