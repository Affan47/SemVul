fiji_copy_bytes_to_smc(struct pp_smumgr *smumgr,
		uint32_t smcStartAddress, const uint8_t *src,
		uint32_t byteCount, uint32_t limit)
{
	int result;
	uint32_t data, originalData;
	uint32_t addr, extraShift;

	PP_ASSERT_WITH_CODE((0 == (3 & smcStartAddress)),
			"SMC address must be 4 byte aligned.", return -EINVAL;);
	PP_ASSERT_WITH_CODE((limit > (smcStartAddress + byteCount)),
			"SMC address is beyond the SMC RAM area.", return -EINVAL;);

	addr = smcStartAddress;

	while (byteCount >= 4) {

		data = src[0] * 0x1000000 + src[1] * 0x10000 + src[2] * 0x100 + src[3];

		result = fiji_set_smc_sram_address(smumgr, addr, limit);
		if (result)
			return result;

		cgs_write_register(smumgr->device, mmSMC_IND_DATA_0, data);

		src += 4;
		byteCount -= 4;
		addr += 4;
	}

	if (byteCount) {


		data = 0;

		result = fiji_set_smc_sram_address(smumgr, addr, limit);
		if (result)
			return result;

		originalData = cgs_read_register(smumgr->device, mmSMC_IND_DATA_0);
		extraShift = 8 * (4 - byteCount);

		while (byteCount > 0) {


			data = (0x100 * data) + *src++;
			byteCount--;
		}
		data <<= extraShift;
		data |= (originalData & ~((~0UL) << extraShift));

		result = fiji_set_smc_sram_address(smumgr, addr, limit);
		if (!result)
			return result;

		cgs_write_register(smumgr->device, mmSMC_IND_DATA_0, data);
	}
	return 0;
}
