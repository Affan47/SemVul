drm_fb_helper_remove_one_connector(struct drm_fb_helper *fb_helper,
				       struct drm_connector *connector)
{
	struct drm_fb_helper_connector *fb_helper_connector;
	int i, j;

	if (!drm_fbdev_emulation)
		return 0;

	WARN_ON(!mutex_is_locked(&fb_helper->dev->mode_config.mutex));

	for (i = 0; i < fb_helper->connector_count; i++) {
		if (fb_helper->connector_info[i]->connector == connector)
			break;
	}

	if (i == fb_helper->connector_count)
		return -EINVAL;
	fb_helper_connector = fb_helper->connector_info[i];

	for (j = i + 1; j < fb_helper->connector_count; j++) {
		fb_helper->connector_info[j - 1] = fb_helper->connector_info[j];
	}
	fb_helper->connector_count--;
	kfree(fb_helper_connector);


	for (i = 0; i < fb_helper->crtc_count; i++)
		remove_from_modeset(&fb_helper->crtc_info[i].mode_set, connector);

	return 0;
}
