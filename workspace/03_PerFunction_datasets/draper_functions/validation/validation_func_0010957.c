fiji_smu_start_in_protection_mode(struct amdgpu_device *adev)
{
	int result;
	uint32_t val;
	int i;


	val = RREG32_SMC(ixSMC_SYSCON_RESET_CNTL);
	val = REG_SET_FIELD(val, SMC_SYSCON_RESET_CNTL, rst_reg, 1);
	WREG32_SMC(ixSMC_SYSCON_RESET_CNTL, val);

	result = fiji_smu_upload_firmware_image(adev);
	if (result)
		return result;


	WREG32_SMC(ixSMU_STATUS, 0);


	val = RREG32_SMC(ixSMC_SYSCON_CLOCK_CNTL_0);
	val = REG_SET_FIELD(val, SMC_SYSCON_CLOCK_CNTL_0, ck_disable, 0);
	WREG32_SMC(ixSMC_SYSCON_CLOCK_CNTL_0, val);


	val = RREG32_SMC(ixSMC_SYSCON_RESET_CNTL);
	val = REG_SET_FIELD(val, SMC_SYSCON_RESET_CNTL, rst_reg, 0);
	WREG32_SMC(ixSMC_SYSCON_RESET_CNTL, val);


	val = RREG32_SMC(ixSMU_INPUT_DATA);
	val = REG_SET_FIELD(val, SMU_INPUT_DATA, AUTO_START, 1);
	WREG32_SMC(ixSMU_INPUT_DATA, val);


	WREG32_SMC(ixFIRMWARE_FLAGS, 0);

	for (i = 0; i < adev->usec_timeout; i++) {
		val = RREG32_SMC(ixRCU_UC_EVENTS);
		if (REG_GET_FIELD(val, RCU_UC_EVENTS, INTERRUPTS_ENABLED))
			break;
		udelay(1);
	}

	if (i == adev->usec_timeout) {
		DRM_ERROR("Interrupt is not enabled by firmware\n");
		return -EINVAL;
	}


	fiji_send_msg_to_smc_offset(adev);
	DRM_INFO("[FM]try triger smu start\n");

	for (i = 0; i < adev->usec_timeout; i++) {
		val = RREG32_SMC(ixSMU_STATUS);
		if (REG_GET_FIELD(val, SMU_STATUS, SMU_DONE))
			break;
		udelay(1);
	}

	if (i == adev->usec_timeout) {
		DRM_ERROR("Timeout for SMU start\n");
		return -EINVAL;
	}


	val = RREG32_SMC(ixSMU_STATUS);
	if (!REG_GET_FIELD(val, SMU_STATUS, SMU_PASS)) {
		DRM_ERROR("SMU Firmware start failed\n");
		return -EINVAL;
	}
	DRM_INFO("[FM]smu started\n");

	for (i = 0; i < adev->usec_timeout; i++) {
		val = RREG32_SMC(ixFIRMWARE_FLAGS);
		if(REG_GET_FIELD(val, FIRMWARE_FLAGS, INTERRUPTS_ENABLED))
			break;
		udelay(1);
	}

	if (i == adev->usec_timeout) {
		DRM_ERROR("SMU firmware initialization failed\n");
		return -EINVAL;
	}
	DRM_INFO("[FM]smu initialized\n");

	return 0;
}
