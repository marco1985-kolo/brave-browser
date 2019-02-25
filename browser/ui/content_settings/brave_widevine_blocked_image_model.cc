/* Copyright (c) 2019 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "brave/browser/ui/content_settings/brave_widevine_blocked_image_model.h"

#include <memory>

#include "brave/browser/brave_drm_tab_helper.h"
#include "brave/browser/ui/content_settings/brave_widevine_content_setting_bubble_model.h"
#include "brave/browser/widevine/widevine_utils.h"
#include "chrome/app/vector_icons/vector_icons.h"
#include "content/public/browser/web_contents.h"
#include "ui/base/l10n/l10n_util.h"
#include "ui/gfx/paint_vector_icon.h"

using content::WebContents;

BraveWidevineBlockedImageModel::BraveWidevineBlockedImageModel(
    ImageType image_type,
    ContentSettingsType content_type)
    : ContentSettingSimpleImageModel(image_type, content_type) {}

bool BraveWidevineBlockedImageModel::UpdateAndGetVisibility(
    WebContents* web_contents) {
  if (!web_contents)
    return false;

  BraveDrmTabHelper* drm_helper =
      BraveDrmTabHelper::FromWebContents(web_contents);
  if (!drm_helper->ShouldShowWidevineOptIn()) {
    return false;
  }

  const gfx::VectorIcon* badge_id = &kBlockedBadgeIcon;
  const gfx::VectorIcon* icon = &kExtensionIcon;
  set_icon(*icon, *badge_id);
  set_explanatory_string_id(GetWidevineBlockedImageMessageResourceId());
  set_tooltip(
      l10n_util::GetStringUTF16(GetWidevineBlockedImageTooltipResourceId()));
  return true;
}

std::unique_ptr<ContentSettingBubbleModel>
BraveWidevineBlockedImageModel::CreateBubbleModelImpl(
    ContentSettingBubbleModel::Delegate* delegate,
    WebContents* web_contents) {
  return std::make_unique<BraveWidevineContentSettingPluginBubbleModel>(
      delegate, web_contents);
}
