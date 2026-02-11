sumo_initialize_m3_arb(struct radeon_device *rdev)
{
	struct sumo_power_info *pi = sumo_get_pi(rdev);
	u32 i;

	if (!pi->enable_dynamic_m3_arbiter)
		return;

	for (i = 0; i < NUMBER_OF_M3ARB_PARAM_SETS; i++)
		WREG32_RCU(MCU_M3ARB_PARAMS + (i * 4),
			   pi->sys_info.csr_m3_arb_cntl_default[i]);

	for (; i < NUMBER_OF_M3ARB_PARAM_SETS * 2; i++)
		WREG32_RCU(MCU_M3ARB_PARAMS + (i * 4),
			   pi->sys_info.csr_m3_arb_cntl_uvd[i % NUMBER_OF_M3ARB_PARAM_SETS]);

	for (; i < NUMBER_OF_M3ARB_PARAM_SETS * 3; i++)
		WREG32_RCU(MCU_M3ARB_PARAMS + (i * 4),
			   pi->sys_info.csr_m3_arb_cntl_fs3d[i % NUMBER_OF_M3ARB_PARAM_SETS]);
}
