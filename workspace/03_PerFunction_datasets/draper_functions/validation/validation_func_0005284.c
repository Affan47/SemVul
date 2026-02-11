intel_crt_get_modes(struct drm_connector *connector)
{
	struct drm_device *dev = connector->dev;
	struct drm_i915_private *dev_priv = dev->dev_private;
	struct intel_crt *crt = intel_attached_crt(connector);
	struct intel_encoder *intel_encoder = &crt->base;
	enum intel_display_power_domain power_domain;
	int ret;
	struct i2c_adapter *i2c;

	power_domain = intel_display_port_power_domain(intel_encoder);
	intel_display_power_get(dev_priv, power_domain);

	i2c = intel_gmbus_get_adapter(dev_priv, dev_priv->vbt.crt_ddc_pin);
	ret = intel_crt_ddc_get_modes(connector, i2c);
	if (ret || !IS_G4X(dev))
		goto out;


	i2c = intel_gmbus_get_adapter(dev_priv, GMBUS_PIN_DPB);
	ret = intel_crt_ddc_get_modes(connector, i2c);

out:
	intel_display_power_put(dev_priv, power_domain);

	return ret;
}
