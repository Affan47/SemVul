wait_for_register_fw(struct drm_i915_private *dev_priv,
				i915_reg_t reg,
				const u32 mask,
				const u32 value,
				const unsigned long timeout_ms)
{
	return wait_for((I915_READ_FW(reg) & mask) == value, timeout_ms);
}
