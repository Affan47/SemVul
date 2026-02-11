intel_guc_resume(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	struct intel_guc *guc = &dev_priv->guc;
	struct intel_context *ctx;
	u32 data[3];

	if (!i915.enable_guc_submission)
		return 0;

	ctx = dev_priv->ring[RCS].default_context;

	data[0] = HOST2GUC_ACTION_EXIT_S_STATE;
	data[1] = GUC_POWER_D0;

	data[2] = i915_gem_obj_ggtt_offset(ctx->engine[RCS].state);

	return host2guc_action(guc, data, ARRAY_SIZE(data));
}
