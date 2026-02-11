cz_write_smc_sram_dword(struct amdgpu_device *adev, u32 smc_address,
						u32 value, u32 limit)
{
	int ret;

	ret = cz_set_smc_sram_address(adev, smc_address, limit);
	if (ret)
		return ret;

	WREG32(mmMP0PUB_IND_DATA_0, value);

	return 0;
}
