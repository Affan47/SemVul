dce_v8_0_early_init(void *handle)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;

	adev->audio_endpt_rreg = &dce_v8_0_audio_endpt_rreg;
	adev->audio_endpt_wreg = &dce_v8_0_audio_endpt_wreg;

	dce_v8_0_set_display_funcs(adev);
	dce_v8_0_set_irq_funcs(adev);

	switch (adev->asic_type) {
	case CHIP_BONAIRE:
	case CHIP_HAWAII:
		adev->mode_info.num_crtc = 6;
		adev->mode_info.num_hpd = 6;
		adev->mode_info.num_dig = 6;
		break;
	case CHIP_KAVERI:
		adev->mode_info.num_crtc = 4;
		adev->mode_info.num_hpd = 6;
		adev->mode_info.num_dig = 7;
		break;
	case CHIP_KABINI:
	case CHIP_MULLINS:
		adev->mode_info.num_crtc = 2;
		adev->mode_info.num_hpd = 6;
		adev->mode_info.num_dig = 6;
		break;
	default:

		return -EINVAL;
	}

	return 0;
}
