drm_mode_config_reset(struct drm_device *dev)
{
	struct drm_crtc *crtc;
	struct drm_plane *plane;
	struct drm_encoder *encoder;
	struct drm_connector *connector;

	drm_for_each_plane(plane, dev)
		if (plane->funcs->reset)
			plane->funcs->reset(plane);

	drm_for_each_crtc(crtc, dev)
		if (crtc->funcs->reset)
			crtc->funcs->reset(crtc);

	drm_for_each_encoder(encoder, dev)
		if (encoder->funcs->reset)
			encoder->funcs->reset(encoder);

	mutex_lock(&dev->mode_config.mutex);
	drm_for_each_connector(connector, dev)
		if (connector->funcs->reset)
			connector->funcs->reset(connector);
	mutex_unlock(&dev->mode_config.mutex);
}
