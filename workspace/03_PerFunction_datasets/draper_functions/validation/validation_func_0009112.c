ilk_compute_wm_level(const struct drm_i915_private *dev_priv,
				 const struct intel_crtc *intel_crtc,
				 int level,
				 struct intel_crtc_state *cstate,
				 struct intel_wm_level *result)
{
	struct intel_plane *intel_plane;
	uint16_t pri_latency = dev_priv->wm.pri_latency[level];
	uint16_t spr_latency = dev_priv->wm.spr_latency[level];
	uint16_t cur_latency = dev_priv->wm.cur_latency[level];


	if (level > 0) {
		pri_latency *= 5;
		spr_latency *= 5;
		cur_latency *= 5;
	}

	for_each_intel_plane_on_crtc(dev_priv->dev, intel_crtc, intel_plane) {
		struct intel_plane_state *pstate =
			to_intel_plane_state(intel_plane->base.state);

		switch (intel_plane->base.type) {
		case DRM_PLANE_TYPE_PRIMARY:
			result->pri_val = ilk_compute_pri_wm(cstate, pstate,
							     pri_latency,
							     level);
			result->fbc_val = ilk_compute_fbc_wm(cstate, pstate,
							     result->pri_val);
			break;
		case DRM_PLANE_TYPE_OVERLAY:
			result->spr_val = ilk_compute_spr_wm(cstate, pstate,
							     spr_latency);
			break;
		case DRM_PLANE_TYPE_CURSOR:
			result->cur_val = ilk_compute_cur_wm(cstate, pstate,
							     cur_latency);
			break;
		}
	}

	result->enable = true;
}
