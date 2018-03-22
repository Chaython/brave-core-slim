/* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0. If a copy of the MPL was not distributed with this file,
* You can obtain one at http://mozilla.org/MPL/2.0/. */

import * as shieldState from '../types/state/shieldsPannelState'

export const getActiveTabId: shieldState.GetActiveTabId = (state) => state.windows[state.currentWindowId]

export const getActiveTabData: shieldState.GetActiveTabData = (state) => state.tabs[getActiveTabId(state)]

export const updateActiveTab: shieldState.UpdateActiveTab = (state, windowId, tabId) => {
  let windows: shieldState.Windows = { ...state.windows } || {}
  windows[windowId] = tabId
  return { ...state, windows }
}

export const removeWindowInfo: shieldState.RemoveWindowInfo = (state, windowId) => {
  const windows: shieldState.Windows = { ...state.windows }
  delete windows[windowId]
  return { ...state, windows }
}

export const updateFocusedWindow: shieldState.UpdateFocusedWindow = (state, windowId) =>
  ({ ...state, currentWindowId: windowId })

export const updateTabShieldsData: shieldState.UpdateTabShieldsData = (state, tabId, details) => {
  const tabs: shieldState.Tabs = { ...state.tabs }

  tabs[tabId] = { ...{
    adsBlocked: 0,
    trackersBlocked: 0,
    httpsRedirected: 0,
    javascriptBlocked: 0,
    fingerprintingBlocked: 0,
    braveShields: 'allow',
    ads: 'allow',
    trackers: 'allow',
    httpUpgradableResources: 'allow',
    javascript: 'allow',
    fingerprinting: 'allow',
    controlsOpen: true,
    javascriptBlockedOrigins: []
  },
    ...tabs[tabId],
    ...details
  }
  state = { ...state, tabs }
  return state
}

export const updateResourceBlocked: shieldState.UpdateResourceBlocked = (state, tabId, blockType, subresource) => {
  const tabs: shieldState.Tabs = { ...state.tabs }
  tabs[tabId] = { ...{ adsBlocked: 0, trackersBlocked: 0, httpsRedirected: 0, javascriptBlocked: 0, fingerprintingBlocked: 0, javascriptBlockedOrigins: [] }, ...tabs[tabId] }
  if (blockType === 'ads') {
    tabs[tabId].adsBlocked++
  } else if (blockType === 'trackers') {
    tabs[tabId].trackersBlocked++
  } else if (blockType === 'httpUpgradableResources') {
    tabs[tabId].httpsRedirected++
  } else if (blockType === 'javascript') {
    const origin = new window.URL(subresource).origin + '/'
    tabs[tabId].javascriptBlocked++
    tabs[tabId].javascriptBlockedOrigins = Array.from(new Set([...tabs[tabId].javascriptBlockedOrigins, origin]))
  } else if (blockType === 'fingerprinting') {
    tabs[tabId].fingerprintingBlocked++
  }
  return { ...state, tabs }
}

export const resetBlockingStats: shieldState.ResetBlockingStats = (state, tabId) => {
  const tabs: shieldState.Tabs = { ...state.tabs }
  tabs[tabId] = { ...tabs[tabId], ...{ adsBlocked: 0, trackersBlocked: 0, httpsRedirected: 0, javascriptBlocked: 0, fingerprintingBlocked: 0, javascriptBlockedOrigins: [] } }
  tabs[tabId].adsBlocked = 0
  tabs[tabId].trackersBlocked = 0
  tabs[tabId].httpsRedirected = 0
  tabs[tabId].javascriptBlocked = 0
  tabs[tabId].fingerprintingBlocked = 0
  tabs[tabId].javascriptBlockedOrigins = []
  return { ...state, tabs }
}
