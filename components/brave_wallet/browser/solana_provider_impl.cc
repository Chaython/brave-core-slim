/* Copyright (c) 2022 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "brave/components/brave_wallet/browser/solana_provider_impl.h"

#include <utility>
#include <vector>

#include "base/notreached.h"
#include "base/values.h"
#include "brave/components/brave_wallet/browser/brave_wallet_provider_delegate.h"
#include "brave/components/brave_wallet/browser/keyring_service.h"
#include "components/grit/brave_components_strings.h"
#include "ui/base/l10n/l10n_util.h"

namespace brave_wallet {

SolanaProviderImpl::SolanaProviderImpl(
    KeyringService* keyring_service,
    std::unique_ptr<BraveWalletProviderDelegate> delegate)
    : keyring_service_(keyring_service),
      delegate_(std::move(delegate)),
      weak_factory_(this) {}
SolanaProviderImpl::~SolanaProviderImpl() = default;

void SolanaProviderImpl::Init(
    ::mojo::PendingRemote<mojom::SolanaEventsListener> events_listener) {
  if (!events_listener_.is_bound()) {
    events_listener_.Bind(std::move(events_listener));
  }
}

void SolanaProviderImpl::Connect(absl::optional<base::Value> arg,
                                 ConnectCallback callback) {
  // TODO(darkdh): handle onlyIfTrusted when it exists
  DCHECK(delegate_);
  delegate_->RequestSolanaPermission(
      base::BindOnce(&SolanaProviderImpl::OnConnect, weak_factory_.GetWeakPtr(),
                     std::move(callback)));
}

void SolanaProviderImpl::Disconnect() {
  NOTIMPLEMENTED();
}

void SolanaProviderImpl::IsConnected(IsConnectedCallback callback) {
  NOTIMPLEMENTED();
  std::move(callback).Run(false);
}

void SolanaProviderImpl::GetPublicKey(GetPublicKeyCallback callback) {
  NOTIMPLEMENTED();
  std::move(callback).Run("");
}

void SolanaProviderImpl::SignTransaction(
    const std::string& encoded_serialized_msg,
    SignTransactionCallback callback) {
  NOTIMPLEMENTED();
  std::move(callback).Run(mojom::SolanaProviderError::kInternalError, "",
                          std::vector<uint8_t>());
}

void SolanaProviderImpl::SignAllTransactions(
    const std::vector<std::string>& encoded_serialized_msgs,
    SignAllTransactionsCallback callback) {
  NOTIMPLEMENTED();
  std::move(callback).Run(mojom::SolanaProviderError::kInternalError, "",
                          std::vector<std::vector<uint8_t>>());
}

void SolanaProviderImpl::SignAndSendTransaction(
    const std::string& encoded_serialized_msg,
    SignAndSendTransactionCallback callback) {
  base::Value result(base::Value::Type::DICTIONARY);
  NOTIMPLEMENTED();
  std::move(callback).Run(mojom::SolanaProviderError::kInternalError, "",
                          std::move(result));
}

void SolanaProviderImpl::SignMessage(
    const std::string& encoded_msg,
    const absl::optional<std::string>& display_encoding,
    SignMessageCallback callback) {
  base::Value result(base::Value::Type::DICTIONARY);
  NOTIMPLEMENTED();
  std::move(callback).Run(mojom::SolanaProviderError::kInternalError, "",
                          std::move(result));
}

void SolanaProviderImpl::Request(base::Value arg, RequestCallback callback) {
  base::Value result(base::Value::Type::DICTIONARY);
  NOTIMPLEMENTED();
  std::move(callback).Run(mojom::SolanaProviderError::kInternalError, "",
                          std::move(result));
}

void SolanaProviderImpl::OnConnect(ConnectCallback callback,
                                   const absl::optional<std::string>& account,
                                   mojom::SolanaProviderError error,
                                   const std::string& error_message) {
  if (error == mojom::SolanaProviderError::kSuccess && !account) {
    std::move(callback).Run(
        mojom::SolanaProviderError::kUserRejectedRequest,
        l10n_util::GetStringUTF8(IDS_WALLET_USER_REJECTED_REQUEST), "");
  } else {
    std::move(callback).Run(
        error, error_message,
        error == mojom::SolanaProviderError::kSuccess ? *account : "");
  }
}

}  // namespace brave_wallet
