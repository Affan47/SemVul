htotal_calculate(struct drm_display_mode *mode)
{
	u32 htotal, new_crtc_htotal;

	htotal = (mode->crtc_hdisplay - 1) | ((mode->crtc_htotal - 1) << 16);


	new_crtc_htotal = (mode->crtc_htotal - 1) * 200 * 1000 / mode->clock;

	DRM_DEBUG_KMS("new crtc htotal 0x%4x\n", new_crtc_htotal);
	return (mode->crtc_hdisplay - 1) | (new_crtc_htotal << 16);
}
