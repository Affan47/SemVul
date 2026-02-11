edid_fixup_preferred(struct drm_connector *connector,
				 u32 quirks)
{
	struct drm_display_mode *t, *cur_mode, *preferred_mode;
	int target_refresh = 0;
	int cur_vrefresh, preferred_vrefresh;

	if (list_empty(&connector->probed_modes))
		return;

	if (quirks & EDID_QUIRK_PREFER_LARGE_60)
		target_refresh = 60;
	if (quirks & EDID_QUIRK_PREFER_LARGE_75)
		target_refresh = 75;

	preferred_mode = list_first_entry(&connector->probed_modes,
					  struct drm_display_mode, head);

	list_for_each_entry_safe(cur_mode, t, &connector->probed_modes, head) {
		cur_mode->type &= ~DRM_MODE_TYPE_PREFERRED;

		if (cur_mode == preferred_mode)
			continue;


		if (MODE_SIZE(cur_mode) > MODE_SIZE(preferred_mode))
			preferred_mode = cur_mode;

		cur_vrefresh = cur_mode->vrefresh ?
			cur_mode->vrefresh : drm_mode_vrefresh(cur_mode);
		preferred_vrefresh = preferred_mode->vrefresh ?
			preferred_mode->vrefresh : drm_mode_vrefresh(preferred_mode);

		if ((MODE_SIZE(cur_mode) == MODE_SIZE(preferred_mode)) &&
		    MODE_REFRESH_DIFF(cur_vrefresh, target_refresh) <
		    MODE_REFRESH_DIFF(preferred_vrefresh, target_refresh)) {
			preferred_mode = cur_mode;
		}
	}

	preferred_mode->type |= DRM_MODE_TYPE_PREFERRED;
}
