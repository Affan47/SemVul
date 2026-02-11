i915_driver_cleanup_hw(struct drm_i915_private *dev_priv)
{
	struct drm_device *dev = dev_priv->dev;
	struct i915_ggtt *ggtt = &dev_priv->ggtt;

	if (dev->pdev->msi_enabled)
		pci_disable_msi(dev->pdev);

	pm_qos_remove_request(&dev_priv->pm_qos);
	arch_phys_wc_del(ggtt->mtrr);
	io_mapping_free(ggtt->mappable);
	i915_ggtt_cleanup_hw(dev);
}
