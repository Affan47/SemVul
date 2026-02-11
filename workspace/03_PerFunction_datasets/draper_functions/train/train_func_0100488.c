intel_ddi_get_config(struct intel_encoder *encoder,
			  struct intel_crtc_state *pipe_config)
{
	struct drm_i915_private *dev_priv = encoder->base.dev->dev_private;
	struct intel_crtc *intel_crtc = to_intel_crtc(encoder->base.crtc);
	enum transcoder cpu_transcoder = pipe_config->cpu_transcoder;
	struct intel_hdmi *intel_hdmi;
	u32 temp, flags = 0;


	if (WARN_ON(transcoder_is_dsi(cpu_transcoder)))
		return;

	temp = I915_READ(TRANS_DDI_FUNC_CTL(cpu_transcoder));
	if (temp & TRANS_DDI_PHSYNC)
		flags |= DRM_MODE_FLAG_PHSYNC;
	else
		flags |= DRM_MODE_FLAG_NHSYNC;
	if (temp & TRANS_DDI_PVSYNC)
		flags |= DRM_MODE_FLAG_PVSYNC;
	else
		flags |= DRM_MODE_FLAG_NVSYNC;

	pipe_config->base.adjusted_mode.flags |= flags;

	switch (temp & TRANS_DDI_BPC_MASK) {
	case TRANS_DDI_BPC_6:
		pipe_config->pipe_bpp = 18;
		break;
	case TRANS_DDI_BPC_8:
		pipe_config->pipe_bpp = 24;
		break;
	case TRANS_DDI_BPC_10:
		pipe_config->pipe_bpp = 30;
		break;
	case TRANS_DDI_BPC_12:
		pipe_config->pipe_bpp = 36;
		break;
	default:
		break;
	}

	switch (temp & TRANS_DDI_MODE_SELECT_MASK) {
	case TRANS_DDI_MODE_SELECT_HDMI:
		pipe_config->has_hdmi_sink = true;
		intel_hdmi = enc_to_intel_hdmi(&encoder->base);

		if (intel_hdmi->infoframe_enabled(&encoder->base, pipe_config))
			pipe_config->has_infoframe = true;

	case TRANS_DDI_MODE_SELECT_DVI:
		pipe_config->lane_count = 4;
		break;
	case TRANS_DDI_MODE_SELECT_FDI:
		break;
	case TRANS_DDI_MODE_SELECT_DP_SST:
	case TRANS_DDI_MODE_SELECT_DP_MST:
		pipe_config->has_dp_encoder = true;
		pipe_config->lane_count =
			((temp & DDI_PORT_WIDTH_MASK) >> DDI_PORT_WIDTH_SHIFT) + 1;
		intel_dp_get_m_n(intel_crtc, pipe_config);
		break;
	default:
		break;
	}

	pipe_config->has_audio =
		intel_ddi_is_audio_enabled(dev_priv, intel_crtc);

	if (encoder->type == INTEL_OUTPUT_EDP && dev_priv->vbt.edp.bpp &&
	    pipe_config->pipe_bpp > dev_priv->vbt.edp.bpp) {


		DRM_DEBUG_KMS("pipe has %d bpp for eDP panel, overriding BIOS-provided max %d bpp\n",
			      pipe_config->pipe_bpp, dev_priv->vbt.edp.bpp);
		dev_priv->vbt.edp.bpp = pipe_config->pipe_bpp;
	}

	intel_ddi_clock_get(encoder, pipe_config);
}
