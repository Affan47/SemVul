multiple_pipes_ok(struct intel_crtc *crtc)
{
	struct drm_i915_private *dev_priv = crtc->base.dev->dev_private;
	struct drm_plane *primary = crtc->base.primary;
	struct intel_fbc *fbc = &dev_priv->fbc;
	enum pipe pipe = crtc->pipe;


	if (!no_fbc_on_multiple_pipes(dev_priv))
		return true;

	WARN_ON(!drm_modeset_is_locked(&primary->mutex));

	if (to_intel_plane_state(primary->state)->visible)
		fbc->visible_pipes_mask |= (1 << pipe);
	else
		fbc->visible_pipes_mask &= ~(1 << pipe);

	return (fbc->visible_pipes_mask & ~(1 << pipe)) != 0;
}
