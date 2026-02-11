assert_can_disable_dc6(struct drm_i915_private *dev_priv)
{


	if (dev_priv->power_domains.initializing)
		return;

	assert_csr_loaded(dev_priv);
	WARN_ONCE(!(I915_READ(DC_STATE_EN) & DC_STATE_EN_UPTO_DC6),
		  "DC6 already programmed to be disabled.\n");
}
