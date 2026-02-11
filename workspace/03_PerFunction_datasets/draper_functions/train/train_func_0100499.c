r128_cce_init(struct drm_device *dev, void *data, struct drm_file *file_priv)
{
	drm_r128_init_t *init = data;

	DRM_DEBUG("\n");

	LOCK_TEST_WITH_RETURN(dev, file_priv);

	switch (init->func) {
	case R128_INIT_CCE:
		return r128_do_init_cce(dev, init);
	case R128_CLEANUP_CCE:
		return r128_do_cleanup_cce(dev);
	}

	return -EINVAL;
}
