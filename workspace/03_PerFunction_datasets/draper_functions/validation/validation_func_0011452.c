vmw_kms_ldu_init_display(struct vmw_private *dev_priv)
{
	struct drm_device *dev = dev_priv->dev;
	int i, ret;

	if (dev_priv->ldu_priv) {
		DRM_INFO("ldu system already on\n");
		return -EINVAL;
	}

	dev_priv->ldu_priv = kmalloc(sizeof(*dev_priv->ldu_priv), GFP_KERNEL);
	if (!dev_priv->ldu_priv)
		return -ENOMEM;

	INIT_LIST_HEAD(&dev_priv->ldu_priv->active);
	dev_priv->ldu_priv->num_active = 0;
	dev_priv->ldu_priv->last_num_active = 0;
	dev_priv->ldu_priv->fb = NULL;


	if (dev_priv->capabilities & SVGA_CAP_MULTIMON)
		ret = drm_vblank_init(dev, VMWGFX_NUM_DISPLAY_UNITS);
	else
		ret = drm_vblank_init(dev, 1);
	if (ret != 0)
		goto err_free;

	ret = drm_mode_create_dirty_info_property(dev);
	if (ret != 0)
		goto err_vblank_cleanup;

	if (dev_priv->capabilities & SVGA_CAP_MULTIMON)
		for (i = 0; i < VMWGFX_NUM_DISPLAY_UNITS; ++i)
			vmw_ldu_init(dev_priv, i);
	else
		vmw_ldu_init(dev_priv, 0);

	dev_priv->active_display_unit = vmw_du_legacy;

	DRM_INFO("Legacy Display Unit initialized\n");

	return 0;

err_vblank_cleanup:
	drm_vblank_cleanup(dev);
err_free:
	kfree(dev_priv->ldu_priv);
	dev_priv->ldu_priv = NULL;
	return ret;
}
