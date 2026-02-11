gfx_v7_0_enter_rlc_safe_mode(struct amdgpu_device *adev)
{
	u32 tmp, i, mask;

	tmp = 0x1 | (1 << 1);
	WREG32(mmRLC_GPR_REG2, tmp);

	mask = RLC_GPM_STAT__GFX_POWER_STATUS_MASK |
		RLC_GPM_STAT__GFX_CLOCK_STATUS_MASK;
	for (i = 0; i < adev->usec_timeout; i++) {
		if ((RREG32(mmRLC_GPM_STAT) & mask) == mask)
			break;
		udelay(1);
	}

	for (i = 0; i < adev->usec_timeout; i++) {
		if ((RREG32(mmRLC_GPR_REG2) & 0x1) == 0)
			break;
		udelay(1);
	}
}
