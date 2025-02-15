/* Copyright (c) 2022 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "base/test/mock_callback.h"
#include "brave/components/brave_ads/common/interfaces/brave_ads.mojom-shared.h"
#include "brave/components/brave_ads/core/ad_type.h"
#include "brave/components/brave_ads/core/confirmation_type.h"
#include "brave/components/brave_ads/core/internal/account/transactions/transactions_unittest_util.h"
#include "brave/components/brave_ads/core/internal/ads/ad_events/ad_event_unittest_util.h"
#include "brave/components/brave_ads/core/internal/ads/ad_unittest_constants.h"
#include "brave/components/brave_ads/core/internal/ads/serving/permission_rules/permission_rules_unittest_util.h"
#include "brave/components/brave_ads/core/internal/catalog/catalog_url_request_builder_util.h"
#include "brave/components/brave_ads/core/internal/common/unittest/unittest_base.h"
#include "brave/components/brave_ads/core/internal/common/unittest/unittest_mock_util.h"
#include "brave/components/brave_ads/core/internal/history/history_unittest_util.h"
#include "net/http/http_status_code.h"

// npm run test -- brave_unit_tests --filter=BraveAds*

namespace brave_ads {

class BraveAdsPromotedContentAdIntegrationTest : public UnitTestBase {
 protected:
  void SetUp() override {
    UnitTestBase::SetUpForTesting(/*is_integration_test*/ true);

    ForcePermissionRulesForTesting();
  }

  void SetUpMocks() override {
    const URLResponseMap url_responses = {
        {BuildCatalogUrlPath(),
         {{net::HTTP_OK,
           /*response_body*/ "/catalog_with_promoted_content_ad.json"}}}};
    MockUrlResponses(ads_client_mock_, url_responses);

    EXPECT_CALL(ads_client_mock_, RecordP2AEvents).Times(0);
  }

  void TriggerPromotedContentAdEvent(
      const std::string& placement_id,
      const std::string& creative_instance_id,
      const mojom::PromotedContentAdEventType& event_type,
      const bool should_fire_event) {
    base::MockCallback<TriggerAdEventCallback> callback;
    EXPECT_CALL(callback, Run(/*success*/ should_fire_event));

    GetAds().TriggerPromotedContentAdEvent(placement_id, creative_instance_id,
                                           event_type, callback.Get());
  }
};

TEST_F(BraveAdsPromotedContentAdIntegrationTest, TriggerViewedEvent) {
  // Arrange

  // Act
  TriggerPromotedContentAdEvent(kPlacementId, kCreativeInstanceId,
                                mojom::PromotedContentAdEventType::kViewed,
                                /*should_fire_event*/ true);

  // Assert
  EXPECT_EQ(1U, GetAdEventCount(AdType::kPromotedContentAd,
                                ConfirmationType::kServed));
  EXPECT_EQ(1U, GetAdEventCount(AdType::kPromotedContentAd,
                                ConfirmationType::kViewed));
  EXPECT_EQ(1U, GetHistoryItemCount());
  EXPECT_EQ(1U, GetTransactionCount());
}

TEST_F(BraveAdsPromotedContentAdIntegrationTest, TriggerClickedEvent) {
  // Arrange
  TriggerPromotedContentAdEvent(kPlacementId, kCreativeInstanceId,
                                mojom::PromotedContentAdEventType::kViewed,
                                /*should_fire_event*/ true);

  // Act
  TriggerPromotedContentAdEvent(kPlacementId, kCreativeInstanceId,
                                mojom::PromotedContentAdEventType::kClicked,
                                /*should_fire_event*/ true);

  // Assert
  EXPECT_EQ(1U, GetAdEventCount(AdType::kPromotedContentAd,
                                ConfirmationType::kServed));
  EXPECT_EQ(1U, GetAdEventCount(AdType::kPromotedContentAd,
                                ConfirmationType::kViewed));
  EXPECT_EQ(1U, GetAdEventCount(AdType::kPromotedContentAd,
                                ConfirmationType::kClicked));
  EXPECT_EQ(2U, GetHistoryItemCount());
  EXPECT_EQ(2U, GetTransactionCount());
}

}  // namespace brave_ads
