radeon_irq_wait(struct drm_device *dev, void *data, struct drm_file *file_priv)
{
	drm_radeon_private_t *dev_priv = dev->dev_private;
	drm_radeon_irq_wait_t *irqwait = data;

	if (!dev_priv) {
		DRM_ERROR("called with no initialization\n");
		return -EINVAL;
	}

	if ((dev_priv->flags & RADEON_FAMILY_MASK) >= CHIP_R600)
		return -EINVAL;

	return radeon_wait_irq(dev, irqwait->irq_seq);
}
