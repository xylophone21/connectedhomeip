/*
 *
 *    Copyright (c) 2022 Project CHIP Authors
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
#include <app-common/zap-generated/cluster-objects.h>
#include <app/InteractionModelEngine.h>
#include <app/data-model/DecodableList.h>
#include <app/util/af-enums.h>
#include <app/util/attribute-filter.h>
#include <app/util/im-client-callbacks.h>
#include <inttypes.h>
#include <lib/support/FunctionTraits.h>
#include <lib/support/Span.h>

// Note: The IMDefaultResponseCallback is a bridge to the old CallbackMgr before IM is landed, so it still accepts EmberAfStatus
// instead of IM status code.
// #6308 should handle IM error code on the application side, either modify this function or remove this.

// Cluster Specific Response Callbacks
typedef void (*OtaSoftwareUpdateProviderClusterApplyUpdateResponseCallback)(void * context, uint8_t action,
                                                                            uint32_t delayedActionTime);
typedef void (*OtaSoftwareUpdateProviderClusterQueryImageResponseCallback)(
    void * context, uint8_t status, uint32_t delayedActionTime, chip::CharSpan imageURI, uint32_t softwareVersion,
    chip::CharSpan softwareVersionString, chip::ByteSpan updateToken, bool userConsentNeeded, chip::ByteSpan metadataForRequestor);
typedef void (*ScenesClusterAddSceneResponseCallback)(void * context, uint8_t status, uint16_t groupId, uint8_t sceneId);
typedef void (*ScenesClusterGetSceneMembershipResponseCallback)(void * context, uint8_t status, uint8_t capacity, uint16_t groupId,
                                                                uint8_t sceneCount,
                                                                /* TYPE WARNING: array array defaults to */ uint8_t * sceneList);
typedef void (*ScenesClusterRemoveAllScenesResponseCallback)(void * context, uint8_t status, uint16_t groupId);
typedef void (*ScenesClusterRemoveSceneResponseCallback)(void * context, uint8_t status, uint16_t groupId, uint8_t sceneId);
typedef void (*ScenesClusterStoreSceneResponseCallback)(void * context, uint8_t status, uint16_t groupId, uint8_t sceneId);
typedef void (*ScenesClusterViewSceneResponseCallback)(void * context, uint8_t status, uint16_t groupId, uint8_t sceneId,
                                                       uint16_t transitionTime, chip::CharSpan sceneName,
                                                       /* TYPE WARNING: array array defaults to */ uint8_t * extensionFieldSets);

// List specific responses
void GroupsClusterAttributeListListAttributeFilter(chip::TLV::TLVReader * data, chip::Callback::Cancelable * onSuccessCallback,
                                                   chip::Callback::Cancelable * onFailureCallback);
typedef void (*GroupsAttributeListListAttributeCallback)(void * context,
                                                         const chip::app::DataModel::DecodableList<chip::AttributeId> & data);
void IdentifyClusterAttributeListListAttributeFilter(chip::TLV::TLVReader * data, chip::Callback::Cancelable * onSuccessCallback,
                                                     chip::Callback::Cancelable * onFailureCallback);
typedef void (*IdentifyAttributeListListAttributeCallback)(void * context,
                                                           const chip::app::DataModel::DecodableList<chip::AttributeId> & data);
void OnOffClusterAttributeListListAttributeFilter(chip::TLV::TLVReader * data, chip::Callback::Cancelable * onSuccessCallback,
                                                  chip::Callback::Cancelable * onFailureCallback);
typedef void (*OnOffAttributeListListAttributeCallback)(void * context,
                                                        const chip::app::DataModel::DecodableList<chip::AttributeId> & data);
void ScenesClusterAttributeListListAttributeFilter(chip::TLV::TLVReader * data, chip::Callback::Cancelable * onSuccessCallback,
                                                   chip::Callback::Cancelable * onFailureCallback);
typedef void (*ScenesAttributeListListAttributeCallback)(void * context,
                                                         const chip::app::DataModel::DecodableList<chip::AttributeId> & data);
