/* Copyright (c) 2019 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_COMPONENTS_BRAVE_ADS_CORE_AD_CONTENT_INFO_H_
#define BRAVE_COMPONENTS_BRAVE_ADS_CORE_AD_CONTENT_INFO_H_

#include <string>

#include "brave/components/brave_ads/common/interfaces/brave_ads.mojom-shared.h"
#include "brave/components/brave_ads/core/ad_type.h"
#include "brave/components/brave_ads/core/confirmation_type.h"
#include "brave/components/brave_ads/core/export.h"
#include "url/gurl.h"

namespace brave_ads {

struct ADS_EXPORT AdContentInfo final {
  AdContentInfo();

  AdContentInfo(const AdContentInfo&);
  AdContentInfo& operator=(const AdContentInfo&);

  AdContentInfo(AdContentInfo&&) noexcept;
  AdContentInfo& operator=(AdContentInfo&&) noexcept;

  ~AdContentInfo();

  AdType type = AdType::kUndefined;
  std::string placement_id;
  std::string creative_instance_id;
  std::string creative_set_id;
  std::string campaign_id;
  std::string advertiser_id;
  std::string segment;
  std::string brand;
  std::string brand_info;
  std::string brand_display_url;
  GURL brand_url;
  mojom::UserReactionType user_reaction_type =
      mojom::UserReactionType::kNeutral;
  ConfirmationType confirmation_type = ConfirmationType::kUndefined;
  bool is_saved = false;
  bool is_flagged = false;
};

bool operator==(const AdContentInfo&, const AdContentInfo&);
bool operator!=(const AdContentInfo&, const AdContentInfo&);

}  // namespace brave_ads

#endif  // BRAVE_COMPONENTS_BRAVE_ADS_CORE_AD_CONTENT_INFO_H_
