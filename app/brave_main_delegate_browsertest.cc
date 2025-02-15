/* Copyright (c) 2019 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "base/feature_list.h"
#include "brave/components/update_client/buildflags.h"
#include "build/build_config.h"
#include "chrome/browser/browser_features.h"
#include "chrome/browser/companion/core/features.h"
#include "chrome/browser/companion/visual_search/features.h"
#include "chrome/browser/dips/dips_features.h"
#include "chrome/browser/domain_reliability/service_factory.h"
#include "chrome/browser/enterprise/connectors/analysis/content_analysis_features.h"
#include "chrome/browser/promos/promos_features.h"
#include "chrome/browser/signin/signin_features.h"
#include "chrome/common/chrome_features.h"
#include "chrome/common/chrome_switches.h"
#include "chrome/test/base/chrome_test_utils.h"
#include "components/aggregation_service/features.h"
#include "components/attribution_reporting/features.h"
#include "components/autofill/core/common/autofill_features.h"
#include "components/autofill/core/common/autofill_payments_features.h"
#include "components/commerce/core/commerce_feature_list.h"
#include "components/component_updater/component_updater_switches.h"
#include "components/content_settings/core/common/features.h"
#include "components/embedder_support/switches.h"
#include "components/history/core/browser/features.h"
#include "components/history_clusters/core/features.h"
#include "components/history_clusters/core/on_device_clustering_features.h"
#include "components/language/core/common/language_experiments.h"
#include "components/lens/lens_features.h"
#include "components/network_time/network_time_tracker.h"
#include "components/omnibox/common/omnibox_features.h"
#include "components/optimization_guide/core/optimization_guide_features.h"
#include "components/page_image_service/features.h"
#include "components/page_info/core/features.h"
#include "components/password_manager/core/common/password_manager_features.h"
#include "components/performance_manager/public/features.h"
#include "components/permissions/features.h"
#include "components/privacy_sandbox/privacy_sandbox_features.h"
#include "components/reading_list/features/reading_list_switches.h"
#include "components/safe_browsing/core/common/features.h"
#include "components/search/ntp_features.h"
#include "components/segmentation_platform/public/features.h"
#include "components/send_tab_to_self/features.h"
#include "components/shared_highlighting/core/common/shared_highlighting_features.h"
#include "components/subresource_filter/core/common/common_features.h"
#include "content/public/common/content_features.h"
#include "content/public/test/browser_test.h"
#include "gpu/config/gpu_finch_features.h"
#include "media/base/media_switches.h"
#include "net/base/features.h"
#include "services/device/public/cpp/device_features.h"
#include "services/network/public/cpp/features.h"
#include "third_party/blink/public/common/features.h"

#if BUILDFLAG(IS_ANDROID)
#include "android_webview/common/aw_features.h"
#include "chrome/test/base/android/android_browser_test.h"
#else
#include "chrome/browser/sharing_hub/sharing_hub_features.h"
#include "chrome/browser/ui/profile_picker.h"
#include "chrome/browser/ui/ui_features.h"
#include "chrome/test/base/in_process_browser_test.h"
#include "components/translate/core/common/translate_util.h"
#include "extensions/common/extension_features.h"
#endif

#if BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_WIN) || BUILDFLAG(IS_MAC)
#include "components/device_signals/core/common/signals_features.h"
#endif

using BraveMainDelegateBrowserTest = PlatformBrowserTest;

const char kBraveOriginTrialsPublicKey[] =
    "bYUKPJoPnCxeNvu72j4EmPuK7tr1PAC7SHh8ld9Mw3E=,"
    "fMS4mpO6buLQ/QMd+zJmxzty/VQ6B1EUZqoCU04zoRU=";

IN_PROC_BROWSER_TEST_F(BraveMainDelegateBrowserTest,
                       DomainReliabilityServiceDisabled) {
  EXPECT_TRUE(base::CommandLine::ForCurrentProcess()->HasSwitch(
      switches::kDisableDomainReliability));
  EXPECT_FALSE(domain_reliability::ShouldCreateService());
}

IN_PROC_BROWSER_TEST_F(BraveMainDelegateBrowserTest,
                       ComponentUpdaterReplacement) {
  EXPECT_TRUE(base::CommandLine::ForCurrentProcess()->HasSwitch(
      switches::kComponentUpdater));
  EXPECT_EQ(base::CommandLine::ForCurrentProcess()->GetSwitchValueASCII(
                switches::kComponentUpdater),
            std::string("url-source=") + BUILDFLAG(UPDATER_PROD_ENDPOINT));
}

IN_PROC_BROWSER_TEST_F(BraveMainDelegateBrowserTest, OriginTrialsTest) {
  EXPECT_TRUE(base::CommandLine::ForCurrentProcess()->HasSwitch(
      embedder_support::kOriginTrialPublicKey));
  EXPECT_EQ(kBraveOriginTrialsPublicKey,
            base::CommandLine::ForCurrentProcess()->GetSwitchValueASCII(
                embedder_support::kOriginTrialPublicKey));
}

IN_PROC_BROWSER_TEST_F(BraveMainDelegateBrowserTest, DisabledFeatures) {
  // Please, keep alphabetized
  const base::Feature* disabled_features[] = {
    &aggregation_service::kAggregationServiceMultipleCloudProviders,
#if BUILDFLAG(IS_ANDROID)
    &android_webview::features::kWebViewAppsPackageNamesServerSideAllowlist,
    &android_webview::features::kWebViewEnumerateDevicesCache,
    &android_webview::features::kWebViewServerSideSampling,
    &android_webview::features::kWebViewMeasureScreenCoverage,
#endif
    &attribution_reporting::kAttributionReportingNullAggregatableReports,
    &autofill::features::kAutofillEnableOfferNotificationForPromoCodes,
    &autofill::features::kAutofillEnableRemadeDownstreamMetrics,
    &autofill::features::test::kAutofillServerCommunication,
    &autofill::features::kAutofillUpstreamAllowAdditionalEmailDomains,
    &blink::features::kAdInterestGroupAPI,
    &blink::features::kAllowURNsInIframes,
    &blink::features::kBackgroundResourceFetch,
    &blink::features::kBiddingAndScoringDebugReportingAPI,
    &blink::features::kBrowsingTopics,
    &blink::features::kBrowsingTopicsXHR,
    &blink::features::kClientHintsMetaEquivDelegateCH,
    &blink::features::kComputePressure,
    &blink::features::kConversionMeasurement,
    &blink::features::kCssSelectorFragmentAnchor,
    &blink::features::kFencedFrames,
    &blink::features::kFledge,
    &blink::features::kFledgeBiddingAndAuctionServer,
    &blink::features::kFledgeConsiderKAnonymity,
    &blink::features::kFledgeEnforceKAnonymity,
    &blink::features::kInterestGroupStorage,
    &blink::features::kParakeet,
    &blink::features::kPrerender2,
    &blink::features::kPrivacySandboxAdsAPIs,
    &blink::features::kPrivateAggregationApi,
    &blink::features::kSharedStorageAPI,
    &blink::features::kSharedStorageSelectURLLimit,
    &blink::features::kSpeculationRulesHeaderEnableThirdPartyOriginTrial,
    &blink::features::kSpeculationRulesPrefetchFuture,
    &blink::features::kSpeculationRulesPrefetchProxy,
    &blink::features::kTextFragmentAnchor,
    &commerce::kCommerceAllowOnDemandBookmarkUpdates,
    &commerce::kCommerceDeveloper,
    &commerce::kCommerceMerchantViewer,
    &commerce::kCommercePriceTracking,
    &commerce::kShoppingList,
    &commerce::kShoppingPDPMetrics,
    &commerce::kRetailCoupons,
    &companion::features::internal::kCompanionEnabledByObservingExpsNavigations,
    &companion::features::internal::kSidePanelCompanion,
    &companion::features::internal::kSidePanelCompanion2,
    &companion::visual_search::features::kVisualSearchSuggestions,
    &content_settings::features::kUserBypassUI,
    &dips::kFeature,
    &enterprise_connectors::kLocalContentAnalysisEnabled,
#if BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_WIN) || BUILDFLAG(IS_MAC)
    &enterprise_signals::features::kDeviceSignalsConsentDialog,
#endif
#if !BUILDFLAG(IS_ANDROID)
    &extensions_features::kExtensionsManifestV3Only,
#endif
#if BUILDFLAG(IS_WIN)
    &features::kAppBoundEncryptionMetrics,
#endif
    &features::kBookmarkTriggerForPrerender2,
#if !BUILDFLAG(IS_ANDROID)
    &features::kCopyLinkToText,
#endif
    &features::kAttributionFencedFrameReportingBeacon,
    &features::kDigitalGoodsApi,
    &features::kExtensionsMenuInAppMenu,
    &features::kFedCm,
    &features::kFedCmIframeSupport,
    &features::kFedCmUserInfo,
    &features::kFedCmWithoutThirdPartyCookies,
    &features::kFirstPartySets,
    &features::kIdleDetection,
    &features::kKAnonymityService,
    &features::kNotificationTriggers,
    &features::kOmniboxTriggerForNoStatePrefetch,
    &features::kOmniboxTriggerForPrerender2,
#if BUILDFLAG(IS_ANDROID)
    &features::kPrivacyGuideAndroidPostMVP,
#endif
    &features::kPrivacySandboxAdsAPIsOverride,
    &features::kSCTAuditing,
    &features::kSignedExchangeReportingForDistributors,
    &features::kSignedHTTPExchange,
    &features::kSupportSearchSuggestionForPrerender2,
    &features::kTabHoverCardImages,
#if !BUILDFLAG(IS_ANDROID)
    &features::kTrustSafetySentimentSurvey,
    &features::kTrustSafetySentimentSurveyV2,
#endif
#if BUILDFLAG(IS_MAC)
    &features::kUseChromiumUpdater,
#endif
    &features::kWebEnvironmentIntegrity,
    &features::kWebOTP,
    &history::kOrganicRepeatableQueries,
    &history::kSyncSegmentsData,
    &history_clusters::kSidePanelJourneys,
    &history_clusters::features::kOnDeviceClustering,
    &history_clusters::features::kOnDeviceClusteringKeywordFiltering,
    &history_clusters::internal::kHistoryClustersInternalsPage,
    &history_clusters::internal::kHistoryClustersNavigationContextClustering,
    &history_clusters::internal::kJourneys,
    &history_clusters::internal::kJourneysImages,
    &history_clusters::internal::kJourneysNamedNewTabGroups,
    &history_clusters::internal::kJourneysZeroStateFiltering,
    &history_clusters::internal::kOmniboxAction,
    &history_clusters::internal::kOmniboxHistoryClusterProvider,
    &history_clusters::internal::kPersistedClusters,
    &history_clusters::internal::kPersistContextAnnotationsInHistoryDb,
#if !BUILDFLAG(IS_ANDROID)
    &kForYouFre,
#endif
    &lens::features::kEnableLensPing,
    &lens::features::kLensStandalone,
    &media::kLiveCaption,
    &net::features::kNoncedPartitionedCookies,
    &net::features::kPartitionedCookies,
    &net::features::kSamePartyAttributeEnabled,
    &network::features::kPrivateStateTokens,
    &network_time::kNetworkTimeServiceQuerying,
    &ntp_features::kNtpAlphaBackgroundCollections,
    &ntp_features::kNtpBackgroundImageErrorDetection,
    &ntp_features::kNtpChromeCartModule,
    &ntp_features::kNtpHistoryClustersModule,
    &ntp_features::kNtpHistoryClustersModuleLoad,
    &omnibox::kInspireMe,
    &omnibox::kOmniboxSteadyStateHeight,
    &omnibox::kRichAutocompletion,
    &optimization_guide::features::kOptimizationHints,
    &optimization_guide::features::kRemoteOptimizationGuideFetching,
    &optimization_guide::features::
        kRemoteOptimizationGuideFetchingAnonymousDataConsent,
    &optimization_guide::features::kOptimizationGuideFetchingForSRP,
    &page_image_service::kImageService,
    &page_image_service::kImageServiceSuggestPoweredImages,
#if !BUILDFLAG(IS_ANDROID)
    &page_info::kPageInfoCookiesSubpage,
    &permissions::features::kPermissionsPromptSurvey,
    &permissions::features::kPermissionStorageAccessAPI,
    &permissions::features::kRecordPermissionExpirationTimestamps,
#endif
    &permissions::features::kPermissionOnDeviceNotificationPredictions,
    &privacy_sandbox::kOverridePrivacySandboxSettingsLocalTesting,
    &privacy_sandbox::kEnforcePrivacySandboxAttestations,
    &privacy_sandbox::kPrivacySandboxSettings3,
    &privacy_sandbox::kPrivacySandboxSettings4,
    &promos_features::kIOSPromoPasswordBubble,
    &safe_browsing::kExtensionTelemetry,
    &safe_browsing::kExtensionTelemetryDeclarativeNetRequestSignal,
    &segmentation_platform::features::kSegmentationPlatformDeviceTier,
    &segmentation_platform::features::kSegmentationPlatformFeature,
    &send_tab_to_self::kSendTabToSelfSigninPromo,
    &shared_highlighting::kIOSSharedHighlightingV2,
    &shared_highlighting::kSharedHighlightingAmp,
    &shared_highlighting::kSharedHighlightingManager,
    &subresource_filter::kAdTagging,
#if !BUILDFLAG(IS_ANDROID)
    &translate::kTFLiteLanguageDetectionEnabled,
#endif
  };

  for (const auto* feature : disabled_features)
    EXPECT_FALSE(base::FeatureList::IsEnabled(*feature)) << feature->name;
}

IN_PROC_BROWSER_TEST_F(BraveMainDelegateBrowserTest, EnabledFeatures) {
  const base::Feature* enabled_features[] = {
    &autofill::features::kAutofillDisableShadowHeuristics,
    &blink::features::kPrefetchPrivacyChanges,
    &blink::features::kReducedReferrerGranularity,
    &blink::features::kReduceUserAgentMinorVersion,
    &features::kHttpsFirstModeV2,
#if BUILDFLAG(IS_WIN)
    &features::kWinrtGeolocationImplementation,
#endif
#if !BUILDFLAG(IS_ANDROID)
    &performance_manager::features::kHeuristicMemorySaver,
    &safe_browsing::kDownloadBubble,
    &safe_browsing::kDownloadBubbleV2,
    &sharing_hub::kDesktopScreenshots,
#endif
    &media::kEnableTabMuting,
    &net::features::kPartitionConnectionsByNetworkIsolationKey,
    &net::features::kPartitionHttpServerPropertiesByNetworkIsolationKey,
    &net::features::kPartitionSSLSessionsByNetworkIsolationKey,
    &net::features::kSplitHostCacheByNetworkIsolationKey,
  };

  for (const auto* feature : enabled_features)
    EXPECT_TRUE(base::FeatureList::IsEnabled(*feature)) << feature->name;

  EXPECT_TRUE(features::kDnsOverHttpsShowUiParam.default_value);
}
