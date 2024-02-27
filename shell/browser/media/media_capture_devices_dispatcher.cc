// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE-CHROMIUM file.

#include "shell/browser/media/media_capture_devices_dispatcher.h"
// #include "base/no_destructor.h"
#include "base/logging.h"
#include "content/public/browser/browser_thread.h"
#include "content/public/browser/media_capture_devices.h"

using content::BrowserThread;

namespace electron {

MediaCaptureDevicesDispatcher* MediaCaptureDevicesDispatcher::GetInstance() {
  static base::NoDestructor<MediaCaptureDevicesDispatcher> instance;
  return instance.get();
}

MediaCaptureDevicesDispatcher::MediaCaptureDevicesDispatcher() {
  // MediaCaptureDevicesDispatcher is a singleton. It should be created on
  // UI thread.
  DCHECK(BrowserThread::CurrentlyOn(BrowserThread::UI));
}

MediaCaptureDevicesDispatcher::~MediaCaptureDevicesDispatcher() = default;

void MediaCaptureDevicesDispatcher::OnAudioCaptureDevicesChanged() {}

void MediaCaptureDevicesDispatcher::OnVideoCaptureDevicesChanged() {}

void MediaCaptureDevicesDispatcher::OnMediaRequestStateChanged(
    int render_process_id,
    int render_view_id,
    int page_request_id,
    const GURL& security_origin,
    blink::mojom::MediaStreamType stream_type,
    content::MediaRequestState state) {}

void MediaCaptureDevicesDispatcher::OnCreatingAudioStream(int render_process_id,
                                                          int render_view_id) {}

void MediaCaptureDevicesDispatcher::OnSetCapturingLinkSecured(
    int render_process_id,
    int render_frame_id,
    int page_request_id,
    blink::mojom::MediaStreamType stream_type,
    bool is_secure) {}

const std::optional<blink::MediaStreamDevice>
MediaCaptureDevicesDispatcher::GetPreferredAudioDeviceForBrowserContext(
    content::BrowserContext* browser_context,
    const std::vector<std::string>& eligible_audio_device_ids) const {
  const auto& devices = GetAudioCaptureDevices();
  return devices.empty() ? std::nullopt : std::make_optional(devices.front());
}

const std::optional<blink::MediaStreamDevice>
MediaCaptureDevicesDispatcher::GetPreferredVideoDeviceForBrowserContext(
    content::BrowserContext* browser_context,
    const std::vector<std::string>& eligible_video_device_ids) const {
  const auto& devices = GetVideoCaptureDevices();
  return devices.empty() ? std::nullopt : std::make_optional(devices.front());
}

}  // namespace electron
