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

// Prevent multiple inclusion
#pragma once

#include <app-common/zap-generated/ids/Clusters.h>
#include <app-common/zap-generated/ids/Commands.h>

#include <controller/CHIPCluster.h>
#include <lib/core/CHIPCallback.h>
#include <lib/support/Span.h>

namespace chip {
namespace Controller {

class DLL_EXPORT ColorControlCluster : public ClusterBase
{
public:
    ColorControlCluster() : ClusterBase(app::Clusters::ColorControl::Id) {}
    ~ColorControlCluster() {}

    // Cluster Commands
    CHIP_ERROR ColorLoopSet(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback, uint8_t updateFlags,
                            uint8_t action, uint8_t direction, uint16_t time, uint16_t startHue, uint8_t optionsMask,
                            uint8_t optionsOverride);
    CHIP_ERROR EnhancedMoveHue(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback, uint8_t moveMode,
                               uint16_t rate, uint8_t optionsMask, uint8_t optionsOverride);
    CHIP_ERROR EnhancedMoveToHue(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                                 uint16_t enhancedHue, uint8_t direction, uint16_t transitionTime, uint8_t optionsMask,
                                 uint8_t optionsOverride);
    CHIP_ERROR EnhancedMoveToHueAndSaturation(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                                              uint16_t enhancedHue, uint8_t saturation, uint16_t transitionTime,
                                              uint8_t optionsMask, uint8_t optionsOverride);
    CHIP_ERROR EnhancedStepHue(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback, uint8_t stepMode,
                               uint16_t stepSize, uint16_t transitionTime, uint8_t optionsMask, uint8_t optionsOverride);
    CHIP_ERROR MoveColor(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback, int16_t rateX,
                         int16_t rateY, uint8_t optionsMask, uint8_t optionsOverride);
    CHIP_ERROR MoveHue(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback, uint8_t moveMode,
                       uint8_t rate, uint8_t optionsMask, uint8_t optionsOverride);
    CHIP_ERROR MoveSaturation(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback, uint8_t moveMode,
                              uint8_t rate, uint8_t optionsMask, uint8_t optionsOverride);
    CHIP_ERROR MoveToColor(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback, uint16_t colorX,
                           uint16_t colorY, uint16_t transitionTime, uint8_t optionsMask, uint8_t optionsOverride);
    CHIP_ERROR MoveToColorTemperature(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                                      uint16_t colorTemperature, uint16_t transitionTime, uint8_t optionsMask,
                                      uint8_t optionsOverride);
    CHIP_ERROR MoveToHue(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback, uint8_t hue,
                         uint8_t direction, uint16_t transitionTime, uint8_t optionsMask, uint8_t optionsOverride);
    CHIP_ERROR MoveToHueAndSaturation(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                                      uint8_t hue, uint8_t saturation, uint16_t transitionTime, uint8_t optionsMask,
                                      uint8_t optionsOverride);
    CHIP_ERROR MoveToSaturation(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                                uint8_t saturation, uint16_t transitionTime, uint8_t optionsMask, uint8_t optionsOverride);
    CHIP_ERROR StepColor(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback, int16_t stepX,
                         int16_t stepY, uint16_t transitionTime, uint8_t optionsMask, uint8_t optionsOverride);
    CHIP_ERROR StepHue(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback, uint8_t stepMode,
                       uint8_t stepSize, uint8_t transitionTime, uint8_t optionsMask, uint8_t optionsOverride);
    CHIP_ERROR StepSaturation(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback, uint8_t stepMode,
                              uint8_t stepSize, uint8_t transitionTime, uint8_t optionsMask, uint8_t optionsOverride);
};

class DLL_EXPORT GroupsCluster : public ClusterBase
{
public:
    GroupsCluster() : ClusterBase(app::Clusters::Groups::Id) {}
    ~GroupsCluster() {}

    // Cluster Commands
    CHIP_ERROR AddGroup(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback, uint16_t groupId,
                        chip::CharSpan groupName);
    CHIP_ERROR AddGroupIfIdentifying(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                                     uint16_t groupId, chip::CharSpan groupName);
    CHIP_ERROR GetGroupMembership(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                                  uint16_t groupList);
    CHIP_ERROR RemoveAllGroups(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);
    CHIP_ERROR RemoveGroup(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback, uint16_t groupId);
    CHIP_ERROR ViewGroup(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback, uint16_t groupId);
};

class DLL_EXPORT IdentifyCluster : public ClusterBase
{
public:
    IdentifyCluster() : ClusterBase(app::Clusters::Identify::Id) {}
    ~IdentifyCluster() {}
};

class DLL_EXPORT OtaSoftwareUpdateProviderCluster : public ClusterBase
{
public:
    OtaSoftwareUpdateProviderCluster() : ClusterBase(app::Clusters::OtaSoftwareUpdateProvider::Id) {}
    ~OtaSoftwareUpdateProviderCluster() {}

    // Cluster Commands
    CHIP_ERROR ApplyUpdateRequest(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                                  chip::ByteSpan updateToken, uint32_t newVersion);
    CHIP_ERROR NotifyUpdateApplied(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                                   chip::ByteSpan updateToken, uint32_t softwareVersion);
    CHIP_ERROR QueryImage(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                          chip::VendorId vendorId, uint16_t productId, uint32_t softwareVersion, uint8_t protocolsSupported,
                          uint16_t hardwareVersion, chip::CharSpan location, bool requestorCanConsent,
                          chip::ByteSpan metadataForProvider);
};

class DLL_EXPORT OnOffCluster : public ClusterBase
{
public:
    OnOffCluster() : ClusterBase(app::Clusters::OnOff::Id) {}
    ~OnOffCluster() {}

    // Cluster Commands
    CHIP_ERROR Off(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);
    CHIP_ERROR On(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);
    CHIP_ERROR Toggle(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);
};

class DLL_EXPORT ScenesCluster : public ClusterBase
{
public:
    ScenesCluster() : ClusterBase(app::Clusters::Scenes::Id) {}
    ~ScenesCluster() {}

    // Cluster Commands
    CHIP_ERROR AddScene(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback, uint16_t groupId,
                        uint8_t sceneId, uint16_t transitionTime, chip::CharSpan sceneName, chip::ClusterId clusterId,
                        uint8_t length, uint8_t value);
    CHIP_ERROR GetSceneMembership(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                                  uint16_t groupId);
    CHIP_ERROR RecallScene(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback, uint16_t groupId,
                           uint8_t sceneId, uint16_t transitionTime);
    CHIP_ERROR RemoveAllScenes(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                               uint16_t groupId);
    CHIP_ERROR RemoveScene(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback, uint16_t groupId,
                           uint8_t sceneId);
    CHIP_ERROR StoreScene(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback, uint16_t groupId,
                          uint8_t sceneId);
    CHIP_ERROR ViewScene(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback, uint16_t groupId,
                         uint8_t sceneId);
};

} // namespace Controller
} // namespace chip
