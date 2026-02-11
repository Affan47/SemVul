amdgpu_atombios_dp_set_tp(struct amdgpu_atombios_dp_link_train_info *dp_info, int tp)
{
	int rtp = 0;


	switch (tp) {
	case DP_TRAINING_PATTERN_1:
		rtp = ATOM_ENCODER_CMD_DP_LINK_TRAINING_PATTERN1;
		break;
	case DP_TRAINING_PATTERN_2:
		rtp = ATOM_ENCODER_CMD_DP_LINK_TRAINING_PATTERN2;
		break;
	case DP_TRAINING_PATTERN_3:
		rtp = ATOM_ENCODER_CMD_DP_LINK_TRAINING_PATTERN3;
			break;
	}
	amdgpu_atombios_encoder_setup_dig_encoder(dp_info->encoder, rtp, 0);


	drm_dp_dpcd_writeb(dp_info->aux, DP_TRAINING_PATTERN_SET, tp);
}
