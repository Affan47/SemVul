i915_error_capture_msg(struct drm_device *dev,
				   struct drm_i915_error_state *error,
				   u32 engine_mask,
				   const char *error_msg)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	u32 ecode;
	int ring_id = -1, len;

	ecode = i915_error_generate_code(dev_priv, error, &ring_id);

	len = scnprintf(error->error_msg, sizeof(error->error_msg),
			"GPU HANG: ecode %d:%d:0x%08x",
			INTEL_INFO(dev)->gen, ring_id, ecode);

	if (ring_id != -1 && error->ring[ring_id].pid != -1)
		len += scnprintf(error->error_msg + len,
				 sizeof(error->error_msg) - len,
				 ", in %s [%d]",
				 error->ring[ring_id].comm,
				 error->ring[ring_id].pid);

	scnprintf(error->error_msg + len, sizeof(error->error_msg) - len,
		  ", reason: %s, action: %s",
		  error_msg,
		  engine_mask ? "reset" : "continue");
}
