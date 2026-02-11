__vxge_hw_legacy_swapper_set(struct vxge_hw_legacy_reg __iomem *legacy_reg)
{
	u64 val64;
	enum vxge_hw_status status = VXGE_HW_OK;

	val64 = readq(&legacy_reg->toc_swapper_fb);

	wmb();

	switch (val64) {
	case VXGE_HW_SWAPPER_INITIAL_VALUE:
		return status;

	case VXGE_HW_SWAPPER_BYTE_SWAPPED_BIT_FLIPPED:
		writeq(VXGE_HW_SWAPPER_READ_BYTE_SWAP_ENABLE,
			&legacy_reg->pifm_rd_swap_en);
		writeq(VXGE_HW_SWAPPER_READ_BIT_FLAP_ENABLE,
			&legacy_reg->pifm_rd_flip_en);
		writeq(VXGE_HW_SWAPPER_WRITE_BYTE_SWAP_ENABLE,
			&legacy_reg->pifm_wr_swap_en);
		writeq(VXGE_HW_SWAPPER_WRITE_BIT_FLAP_ENABLE,
			&legacy_reg->pifm_wr_flip_en);
		break;

	case VXGE_HW_SWAPPER_BYTE_SWAPPED:
		writeq(VXGE_HW_SWAPPER_READ_BYTE_SWAP_ENABLE,
			&legacy_reg->pifm_rd_swap_en);
		writeq(VXGE_HW_SWAPPER_WRITE_BYTE_SWAP_ENABLE,
			&legacy_reg->pifm_wr_swap_en);
		break;

	case VXGE_HW_SWAPPER_BIT_FLIPPED:
		writeq(VXGE_HW_SWAPPER_READ_BIT_FLAP_ENABLE,
			&legacy_reg->pifm_rd_flip_en);
		writeq(VXGE_HW_SWAPPER_WRITE_BIT_FLAP_ENABLE,
			&legacy_reg->pifm_wr_flip_en);
		break;
	}

	wmb();

	val64 = readq(&legacy_reg->toc_swapper_fb);

	if (val64 != VXGE_HW_SWAPPER_INITIAL_VALUE)
		status = VXGE_HW_ERR_SWAPPER_CTRL;

	return status;
}
