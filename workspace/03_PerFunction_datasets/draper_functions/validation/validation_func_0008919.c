skl_ddb_get_pipe_allocation_limits(struct drm_device *dev,
				   const struct intel_crtc_state *cstate,
				   const struct intel_wm_config *config,
				   struct skl_ddb_entry *alloc )
{
	struct drm_crtc *for_crtc = cstate->base.crtc;
	struct drm_crtc *crtc;
	unsigned int pipe_size, ddb_size;
	int nth_active_pipe;

	if (!cstate->base.active) {
		alloc->start = 0;
		alloc->end = 0;
		return;
	}

	if (IS_BROXTON(dev))
		ddb_size = BXT_DDB_SIZE;
	else
		ddb_size = SKL_DDB_SIZE;

	ddb_size -= 4;

	nth_active_pipe = 0;
	for_each_crtc(dev, crtc) {
		if (!to_intel_crtc(crtc)->active)
			continue;

		if (crtc == for_crtc)
			break;

		nth_active_pipe++;
	}

	pipe_size = ddb_size / config->num_pipes_active;
	alloc->start = nth_active_pipe * ddb_size / config->num_pipes_active;
	alloc->end = alloc->start + pipe_size;
}
