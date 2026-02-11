radeon_surface_free(struct drm_device *dev, void *data, struct drm_file *file_priv)
{
	drm_radeon_private_t *dev_priv = dev->dev_private;
	drm_radeon_surface_free_t *memfree = data;

	if (free_surface(file_priv, dev_priv, memfree->address))
		return -EINVAL;
	else
		return 0;
}
