ast_crtc_init(struct drm_device *dev)
{
	struct ast_crtc *crtc;
	int i;

	crtc = kzalloc(sizeof(struct ast_crtc), GFP_KERNEL);
	if (!crtc)
		return -ENOMEM;

	drm_crtc_init(dev, &crtc->base, &ast_crtc_funcs);
	drm_mode_crtc_set_gamma_size(&crtc->base, 256);
	drm_crtc_helper_add(&crtc->base, &ast_crtc_helper_funcs);

	for (i = 0; i < 256; i++) {
		crtc->lut_r[i] = i;
		crtc->lut_g[i] = i;
		crtc->lut_b[i] = i;
	}
	return 0;
}
