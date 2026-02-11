si_load_smc_ucode(struct radeon_device *rdev, u32 limit)
{
	unsigned long flags;
	u32 ucode_start_address;
	u32 ucode_size;
	const u8 *src;
	u32 data;

	if (!rdev->smc_fw)
		return -EINVAL;

	if (rdev->new_fw) {
		const struct smc_firmware_header_v1_0 *hdr =
			(const struct smc_firmware_header_v1_0 *)rdev->smc_fw->data;

		radeon_ucode_print_smc_hdr(&hdr->header);

		ucode_start_address = le32_to_cpu(hdr->ucode_start_addr);
		ucode_size = le32_to_cpu(hdr->header.ucode_size_bytes);
		src = (const u8 *)
			(rdev->smc_fw->data + le32_to_cpu(hdr->header.ucode_array_offset_bytes));
	} else {
		switch (rdev->family) {
		case CHIP_TAHITI:
			ucode_start_address = TAHITI_SMC_UCODE_START;
			ucode_size = TAHITI_SMC_UCODE_SIZE;
			break;
		case CHIP_PITCAIRN:
			ucode_start_address = PITCAIRN_SMC_UCODE_START;
			ucode_size = PITCAIRN_SMC_UCODE_SIZE;
			break;
		case CHIP_VERDE:
			ucode_start_address = VERDE_SMC_UCODE_START;
			ucode_size = VERDE_SMC_UCODE_SIZE;
			break;
		case CHIP_OLAND:
			ucode_start_address = OLAND_SMC_UCODE_START;
			ucode_size = OLAND_SMC_UCODE_SIZE;
			break;
		case CHIP_HAINAN:
			ucode_start_address = HAINAN_SMC_UCODE_START;
			ucode_size = HAINAN_SMC_UCODE_SIZE;
			break;
		default:
			DRM_ERROR("unknown asic in smc ucode loader\n");
			BUG();
		}
		src = (const u8 *)rdev->smc_fw->data;
	}

	if (ucode_size & 3)
		return -EINVAL;

	spin_lock_irqsave(&rdev->smc_idx_lock, flags);
	WREG32(SMC_IND_INDEX_0, ucode_start_address);
	WREG32_P(SMC_IND_ACCESS_CNTL, AUTO_INCREMENT_IND_0, ~AUTO_INCREMENT_IND_0);
	while (ucode_size >= 4) {

		data = (src[0] << 24) | (src[1] << 16) | (src[2] << 8) | src[3];

		WREG32(SMC_IND_DATA_0, data);

		src += 4;
		ucode_size -= 4;
	}
	WREG32_P(SMC_IND_ACCESS_CNTL, 0, ~AUTO_INCREMENT_IND_0);
	spin_unlock_irqrestore(&rdev->smc_idx_lock, flags);

	return 0;
}
