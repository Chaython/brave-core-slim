/* Copyright (c) 2022 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_COMPONENTS_BRAVE_ADS_CORE_INTERNAL_PRIVACY_CHALLENGE_BYPASS_RISTRETTO_BLINDED_TOKEN_UTIL_H_
#define BRAVE_COMPONENTS_BRAVE_ADS_CORE_INTERNAL_PRIVACY_CHALLENGE_BYPASS_RISTRETTO_BLINDED_TOKEN_UTIL_H_

#include <vector>

#include "brave/third_party/challenge_bypass_ristretto_ffi/src/wrapper.h"

namespace brave_ads::privacy::cbr {

class BlindedToken;
class Token;

std::vector<BlindedToken> BlindTokens(const std::vector<Token>& tokens);

std::vector<challenge_bypass_ristretto::BlindedToken> ToRawBlindedTokens(
    const std::vector<BlindedToken>& tokens);

}  // namespace brave_ads::privacy::cbr

#endif  // BRAVE_COMPONENTS_BRAVE_ADS_CORE_INTERNAL_PRIVACY_CHALLENGE_BYPASS_RISTRETTO_BLINDED_TOKEN_UTIL_H_
