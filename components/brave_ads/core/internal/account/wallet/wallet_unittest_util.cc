/* Copyright (c) 2021 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "brave/components/brave_ads/core/internal/account/wallet/wallet_unittest_util.h"

#include "brave/components/brave_ads/core/internal/account/wallet/wallet_info.h"
#include "brave/components/brave_ads/core/internal/account/wallet/wallet_unittest_constants.h"
#include "brave/components/brave_ads/core/internal/account/wallet/wallet_util.h"

namespace brave_ads {

WalletInfo GetWalletForTesting() {
  return ToWallet(kWalletPaymentId, kWalletRecoverySeed).value_or(WalletInfo{});
}

}  // namespace brave_ads
