psb_modeset_cleanup(struct drm_device *dev)
{
	struct drm_psb_private *dev_priv = dev->dev_private;
	if (dev_priv->modeset) {
		mutex_lock(&dev->struct_mutex);

		drm_kms_helper_poll_fini(dev);
		psb_fbdev_fini(dev);
		drm_mode_config_cleanup(dev);

		mutex_unlock(&dev->struct_mutex);
	}
}
