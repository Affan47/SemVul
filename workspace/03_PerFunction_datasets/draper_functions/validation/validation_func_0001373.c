intel_csr_ucode_fini(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;

	if (!HAS_CSR(dev))
		return;

	intel_csr_load_status_set(dev_priv, FW_FAILED);
	kfree(dev_priv->csr.dmc_payload);
}
