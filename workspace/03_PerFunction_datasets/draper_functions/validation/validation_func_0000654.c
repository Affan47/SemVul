guc_disable_doorbell(struct intel_guc *guc,
				 struct i915_guc_client *client)
{
	struct drm_i915_private *dev_priv = guc_to_i915(guc);
	struct guc_doorbell_info *doorbell;
	i915_reg_t drbreg = GEN8_DRBREGL(client->doorbell_id);
	int value;

	doorbell = client->client_base + client->doorbell_offset;

	doorbell->db_status = GUC_DOORBELL_DISABLED;

	I915_WRITE(drbreg, I915_READ(drbreg) & ~GEN8_DRB_VALID);

	value = I915_READ(drbreg);
	WARN_ON((value & GEN8_DRB_VALID) != 0);

	I915_WRITE(GEN8_DRBREGU(client->doorbell_id), 0);
	I915_WRITE(drbreg, 0);


}
