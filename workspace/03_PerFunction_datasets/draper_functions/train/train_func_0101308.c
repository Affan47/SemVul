intel_bios_is_lvds_present(struct drm_i915_private *dev_priv, u8 *i2c_pin)
{
	int i;

	if (!dev_priv->vbt.child_dev_num)
		return true;

	for (i = 0; i < dev_priv->vbt.child_dev_num; i++) {
		union child_device_config *uchild = dev_priv->vbt.child_dev + i;
		struct old_child_dev_config *child = &uchild->old;


		if (child->device_type != DEVICE_TYPE_INT_LFP &&
		    child->device_type != DEVICE_TYPE_LFP)
			continue;

		if (intel_gmbus_is_valid_pin(dev_priv, child->i2c_pin))
			*i2c_pin = child->i2c_pin;


		if (child->addin_offset)
			return true;


		if (dev_priv->opregion.vbt)
			return true;
	}

	return false;
}
