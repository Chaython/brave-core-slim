/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_BROWSER_SEARCH_ENGINES_SEARCH_ENGINE_TRACKER_H_
#define BRAVE_BROWSER_SEARCH_ENGINES_SEARCH_ENGINE_TRACKER_H_

#include "base/memory/raw_ptr.h"
#include "base/memory/singleton.h"
#include "base/scoped_observation.h"
#include "brave/components/time_period_storage/weekly_event_storage.h"
#include "components/keyed_service/content/browser_context_keyed_service_factory.h"
#include "components/keyed_service/core/keyed_service.h"
#include "components/prefs/pref_change_registrar.h"
#include "components/prefs/pref_member.h"
#include "components/search_engines/template_url_service.h"
#include "components/search_engines/template_url_service_observer.h"
#include "extensions/buildflags/buildflags.h"
#include "url/gurl.h"

// Exposed for tests.
constexpr char kDefaultSearchEngineMetric[] = "Brave.Search.DefaultEngine.4";
constexpr char kSwitchSearchEngineMetric[] = "Brave.Search.SwitchEngine";
constexpr char kWebDiscoveryEnabledMetric[] =
    "Brave.Search.WebDiscoveryEnabled";

// Note: append-only enumeration! Never remove any existing values, as this enum
// is used to bucket a UMA histogram, and removing values breaks that.
enum class SearchEngineP3A {
  kOther,
  kGoogle,
  kDuckDuckGo,
  kStartpage,
  kBing,
  kQwant,
  kYandex,
  kEcosia,
  kBrave,
  kDaum,
  kNaver,
  kMaxValue = kNaver,
};

// Note: append-only enumeration! Never remove any existing values, as this enum
// is used to bucket a UMA histogram, and removing values breaks that.
enum class SearchEngineSwitchP3A {
  kNoSwitch,
  kBraveToGoogle,
  kBraveToDDG,
  kBraveToOther,
  kGoogleToBrave,
  kDDGToBrave,
  kOtherToBrave,
  kOtherToOther,
  kMaxValue = kOtherToOther,
};

class SearchEngineTrackerFactory : public BrowserContextKeyedServiceFactory {
 public:
  static SearchEngineTrackerFactory* GetInstance();

 private:
  friend struct base::DefaultSingletonTraits<SearchEngineTrackerFactory>;
  SearchEngineTrackerFactory();
  ~SearchEngineTrackerFactory() override;

  SearchEngineTrackerFactory(const SearchEngineTrackerFactory&) = delete;
  SearchEngineTrackerFactory& operator=(const SearchEngineTrackerFactory&) =
      delete;

  // BrowserContextKeyedServiceFactory overrides:
  KeyedService* BuildServiceInstanceFor(
      content::BrowserContext* context) const override;
  bool ServiceIsCreatedWithBrowserContext() const override;

  void RegisterProfilePrefs(
      user_prefs::PrefRegistrySyncable* registry) override;
};

// Records P3A metrics when default search engine changes.
class SearchEngineTracker : public KeyedService,
                            public TemplateURLServiceObserver {
 public:
  SearchEngineTracker(TemplateURLService* template_url_service,
                      PrefService* profile_prefs,
                      PrefService* local_state);
  ~SearchEngineTracker() override;

  SearchEngineTracker(const SearchEngineTracker&) = delete;
  SearchEngineTracker& operator=(const SearchEngineTracker&) = delete;

 private:
  // TemplateURLServiceObserver overrides:
  void OnTemplateURLServiceChanged() override;

#if BUILDFLAG(ENABLE_EXTENSIONS)
  void RecordWebDiscoveryEnabledP3A();
#endif

  base::ScopedObservation<TemplateURLService, TemplateURLServiceObserver>
      observer_{this};

  void RecordSwitchP3A(const GURL& url);

  // Keeping this to check for changes in |OnTemplateURLServiceChanged|.
  GURL default_search_url_;
  GURL previous_search_url_;
  WeeklyEventStorage switch_record_;

  raw_ptr<PrefService> local_state_;
  raw_ptr<PrefService> profile_prefs_;

  raw_ptr<TemplateURLService> template_url_service_ = nullptr;

#if BUILDFLAG(ENABLE_EXTENSIONS)
  PrefChangeRegistrar pref_change_registrar_;
#endif
};

#endif  // BRAVE_BROWSER_SEARCH_ENGINES_SEARCH_ENGINE_TRACKER_H_
