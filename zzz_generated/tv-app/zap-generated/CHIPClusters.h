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

// Prevent multiple inclusion
#pragma once

#include <app-common/zap-generated/ids/Clusters.h>
#include <app-common/zap-generated/ids/Commands.h>

#include <controller/CHIPCluster.h>
#include <lib/core/CHIPCallback.h>
#include <lib/support/Span.h>

namespace chip {
namespace Controller {

class DLL_EXPORT GeneralCommissioningCluster : public ClusterBase
{
public:
    GeneralCommissioningCluster() : ClusterBase(app::Clusters::GeneralCommissioning::Id) {}
    ~GeneralCommissioningCluster() {}

    // Cluster Commands
    CHIP_ERROR ArmFailSafe(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                           uint16_t expiryLengthSeconds, uint64_t breadcrumb, uint32_t timeoutMs);
    CHIP_ERROR CommissioningComplete(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);
    CHIP_ERROR SetRegulatoryConfig(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                                   uint8_t location, chip::ByteSpan countryCode, uint64_t breadcrumb, uint32_t timeoutMs);

    // Cluster Attributes
    CHIP_ERROR ReadAttributeBreadcrumb(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);
    CHIP_ERROR ReadAttributeBasicCommissioningInfoList(Callback::Cancelable * onSuccessCallback,
                                                       Callback::Cancelable * onFailureCallback);
    CHIP_ERROR ReadAttributeClusterRevision(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);
    CHIP_ERROR WriteAttributeBreadcrumb(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                                        uint64_t value);

private:
};

class DLL_EXPORT NetworkCommissioningCluster : public ClusterBase
{
public:
    NetworkCommissioningCluster() : ClusterBase(app::Clusters::NetworkCommissioning::Id) {}
    ~NetworkCommissioningCluster() {}

    // Cluster Commands
    CHIP_ERROR DisableNetwork(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                              chip::ByteSpan networkID, uint64_t breadcrumb, uint32_t timeoutMs);
    CHIP_ERROR EnableNetwork(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                             chip::ByteSpan networkID, uint64_t breadcrumb, uint32_t timeoutMs);
    CHIP_ERROR GetLastNetworkCommissioningResult(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                                                 uint32_t timeoutMs);
    CHIP_ERROR RemoveNetwork(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                             chip::ByteSpan networkID, uint64_t breadcrumb, uint32_t timeoutMs);
    CHIP_ERROR ScanNetworks(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback, chip::ByteSpan ssid,
                            uint64_t breadcrumb, uint32_t timeoutMs);

    // Cluster Attributes
    CHIP_ERROR ReadAttributeClusterRevision(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);

private:
};

class DLL_EXPORT OperationalCredentialsCluster : public ClusterBase
{
public:
    OperationalCredentialsCluster() : ClusterBase(app::Clusters::OperationalCredentials::Id) {}
    ~OperationalCredentialsCluster() {}

    // Cluster Commands
    CHIP_ERROR AddNOC(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback, chip::ByteSpan NOCValue,
                      chip::ByteSpan ICACValue, chip::ByteSpan IPKValue, chip::NodeId caseAdminNode, uint16_t adminVendorId);
    CHIP_ERROR AddTrustedRootCertificate(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                                         chip::ByteSpan rootCertificate);
    CHIP_ERROR AttestationRequest(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                                  chip::ByteSpan attestationNonce);
    CHIP_ERROR CertificateChainRequest(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                                       uint8_t certificateType);
    CHIP_ERROR OpCSRRequest(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                            chip::ByteSpan CSRNonce);
    CHIP_ERROR RemoveFabric(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                            uint8_t fabricIndex);
    CHIP_ERROR UpdateFabricLabel(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                                 chip::ByteSpan label);

    // Cluster Attributes
    CHIP_ERROR ReadAttributeFabricsList(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);
    CHIP_ERROR ReadAttributeSupportedFabrics(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);
    CHIP_ERROR ReadAttributeCommissionedFabrics(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);
    CHIP_ERROR ReadAttributeTrustedRootCertificates(Callback::Cancelable * onSuccessCallback,
                                                    Callback::Cancelable * onFailureCallback);
    CHIP_ERROR ReadAttributeClusterRevision(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);

private:
};

class DLL_EXPORT AdministratorCommissioningCluster : public ClusterBase
{
public:
    AdministratorCommissioningCluster() : ClusterBase(app::Clusters::AdministratorCommissioning::Id) {}
    ~AdministratorCommissioningCluster() {}

    // Cluster Commands
    CHIP_ERROR OpenBasicCommissioningWindow(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                                            uint16_t commissioningTimeout);
    CHIP_ERROR OpenCommissioningWindow(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                                       uint16_t commissioningTimeout, chip::ByteSpan PAKEVerifier, uint16_t discriminator,
                                       uint32_t iterations, chip::ByteSpan salt, uint16_t passcodeID);
//   CHIP_ERROR RevokeCommissioning(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);

    // Cluster Attributes
 //   CHIP_ERROR ReadAttributeClusterRevision(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);

private:
};

} // namespace Controller
} // namespace chip
