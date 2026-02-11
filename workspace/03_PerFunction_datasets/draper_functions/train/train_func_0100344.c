amdgpu_atombios_encoder_get_encoder_mode(struct drm_encoder *encoder)
{
	struct amdgpu_encoder *amdgpu_encoder = to_amdgpu_encoder(encoder);
	struct drm_connector *connector;
	struct amdgpu_connector *amdgpu_connector;
	struct amdgpu_connector_atom_dig *dig_connector;


	if (amdgpu_encoder_get_dp_bridge_encoder_id(encoder) != ENCODER_OBJECT_ID_NONE)
		return ATOM_ENCODER_MODE_DP;


	if ((amdgpu_encoder->encoder_id == ENCODER_OBJECT_ID_INTERNAL_DVO1) ||
	    (amdgpu_encoder->encoder_id == ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DVO1))
		return ATOM_ENCODER_MODE_DVO;

	connector = amdgpu_get_connector_for_encoder(encoder);


	if (!connector)
		connector = amdgpu_get_connector_for_encoder_init(encoder);
	amdgpu_connector = to_amdgpu_connector(connector);

	switch (connector->connector_type) {
	case DRM_MODE_CONNECTOR_DVII:
	case DRM_MODE_CONNECTOR_HDMIB:
		if (amdgpu_audio != 0) {
			if (amdgpu_connector->use_digital &&
			    (amdgpu_connector->audio == AMDGPU_AUDIO_ENABLE))
				return ATOM_ENCODER_MODE_HDMI;
			else if (drm_detect_hdmi_monitor(amdgpu_connector_edid(connector)) &&
				 (amdgpu_connector->audio == AMDGPU_AUDIO_AUTO))
				return ATOM_ENCODER_MODE_HDMI;
			else if (amdgpu_connector->use_digital)
				return ATOM_ENCODER_MODE_DVI;
			else
				return ATOM_ENCODER_MODE_CRT;
		} else if (amdgpu_connector->use_digital) {
			return ATOM_ENCODER_MODE_DVI;
		} else {
			return ATOM_ENCODER_MODE_CRT;
		}
		break;
	case DRM_MODE_CONNECTOR_DVID:
	case DRM_MODE_CONNECTOR_HDMIA:
	default:
		if (amdgpu_audio != 0) {
			if (amdgpu_connector->audio == AMDGPU_AUDIO_ENABLE)
				return ATOM_ENCODER_MODE_HDMI;
			else if (drm_detect_hdmi_monitor(amdgpu_connector_edid(connector)) &&
				 (amdgpu_connector->audio == AMDGPU_AUDIO_AUTO))
				return ATOM_ENCODER_MODE_HDMI;
			else
				return ATOM_ENCODER_MODE_DVI;
		} else {
			return ATOM_ENCODER_MODE_DVI;
		}
		break;
	case DRM_MODE_CONNECTOR_LVDS:
		return ATOM_ENCODER_MODE_LVDS;
		break;
	case DRM_MODE_CONNECTOR_DisplayPort:
		dig_connector = amdgpu_connector->con_priv;
		if ((dig_connector->dp_sink_type == CONNECTOR_OBJECT_ID_DISPLAYPORT) ||
		    (dig_connector->dp_sink_type == CONNECTOR_OBJECT_ID_eDP)) {
			return ATOM_ENCODER_MODE_DP;
		} else if (amdgpu_audio != 0) {
			if (amdgpu_connector->audio == AMDGPU_AUDIO_ENABLE)
				return ATOM_ENCODER_MODE_HDMI;
			else if (drm_detect_hdmi_monitor(amdgpu_connector_edid(connector)) &&
				 (amdgpu_connector->audio == AMDGPU_AUDIO_AUTO))
				return ATOM_ENCODER_MODE_HDMI;
			else
				return ATOM_ENCODER_MODE_DVI;
		} else {
			return ATOM_ENCODER_MODE_DVI;
		}
		break;
	case DRM_MODE_CONNECTOR_eDP:
		return ATOM_ENCODER_MODE_DP;
	case DRM_MODE_CONNECTOR_DVIA:
	case DRM_MODE_CONNECTOR_VGA:
		return ATOM_ENCODER_MODE_CRT;
		break;
	case DRM_MODE_CONNECTOR_Composite:
	case DRM_MODE_CONNECTOR_SVIDEO:
	case DRM_MODE_CONNECTOR_9PinDIN:

		return ATOM_ENCODER_MODE_TV;

		break;
	}
}
