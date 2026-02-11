i965_update_wm(struct drm_crtc *unused_crtc)
{
	struct drm_device *dev = unused_crtc->dev;
	struct drm_i915_private *dev_priv = dev->dev_private;
	struct drm_crtc *crtc;
	int srwm = 1;
	int cursor_sr = 16;
	bool cxsr_enabled;


	crtc = single_enabled_crtc(dev);
	if (crtc) {

		static const int sr_latency_ns = 12000;
		const struct drm_display_mode *adjusted_mode = &to_intel_crtc(crtc)->config->base.adjusted_mode;
		int clock = adjusted_mode->crtc_clock;
		int htotal = adjusted_mode->crtc_htotal;
		int hdisplay = to_intel_crtc(crtc)->config->pipe_src_w;
		int cpp = drm_format_plane_cpp(crtc->primary->state->fb->pixel_format, 0);
		unsigned long line_time_us;
		int entries;

		line_time_us = max(htotal * 1000 / clock, 1);


		entries = (((sr_latency_ns / line_time_us) + 1000) / 1000) *
			cpp * hdisplay;
		entries = DIV_ROUND_UP(entries, I915_FIFO_LINE_SIZE);
		srwm = I965_FIFO_SIZE - entries;
		if (srwm < 0)
			srwm = 1;
		srwm &= 0x1ff;
		DRM_DEBUG_KMS("self-refresh entries: %d, wm: %d\n",
			      entries, srwm);

		entries = (((sr_latency_ns / line_time_us) + 1000) / 1000) *
			cpp * crtc->cursor->state->crtc_w;
		entries = DIV_ROUND_UP(entries,
					  i965_cursor_wm_info.cacheline_size);
		cursor_sr = i965_cursor_wm_info.fifo_size -
			(entries + i965_cursor_wm_info.guard_size);

		if (cursor_sr > i965_cursor_wm_info.max_wm)
			cursor_sr = i965_cursor_wm_info.max_wm;

		DRM_DEBUG_KMS("self-refresh watermark: display plane %d "
			      "cursor %d\n", srwm, cursor_sr);

		cxsr_enabled = true;
	} else {
		cxsr_enabled = false;

		intel_set_memory_cxsr(dev_priv, false);
	}

	DRM_DEBUG_KMS("Setting FIFO watermarks - A: 8, B: 8, C: 8, SR %d\n",
		      srwm);


	I915_WRITE(DSPFW1, FW_WM(srwm, SR) |
		   FW_WM(8, CURSORB) |
		   FW_WM(8, PLANEB) |
		   FW_WM(8, PLANEA));
	I915_WRITE(DSPFW2, FW_WM(8, CURSORA) |
		   FW_WM(8, PLANEC_OLD));

	I915_WRITE(DSPFW3, FW_WM(cursor_sr, CURSOR_SR));

	if (cxsr_enabled)
		intel_set_memory_cxsr(dev_priv, true);
}
