/* Copyright (c) 2022 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "brave/content/child/brave_runtime_features.h"

#define SetRuntimeFeaturesDefaultsAndUpdateFromArgs \
  SetRuntimeFeaturesDefaultsAndUpdateFromArgs_ChromiumImpl
#include "src/content/child/runtime_features.cc"
#undef SetRuntimeFeaturesDefaultsAndUpdateFromArgs

namespace content {

void SetRuntimeFeaturesDefaultsAndUpdateFromArgs(
    const base::CommandLine& command_line) {
  SetRuntimeFeaturesDefaultsAndUpdateFromArgs_ChromiumImpl(command_line);

  BraveSetRuntimeFeaturesDefaultsAndUpdateFromArgs(command_line);
}

}  // namespace content
