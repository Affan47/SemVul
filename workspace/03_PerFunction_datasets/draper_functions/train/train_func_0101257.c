vxge_hw_vpath_mtu_set(struct __vxge_hw_vpath_handle *vp, u32 new_mtu)
{
	u64 val64;
	enum vxge_hw_status status = VXGE_HW_OK;
	struct __vxge_hw_virtualpath *vpath;

	if (vp == NULL) {
		status = VXGE_HW_ERR_INVALID_HANDLE;
		goto exit;
	}
	vpath = vp->vpath;

	new_mtu += VXGE_HW_MAC_HEADER_MAX_SIZE;

	if ((new_mtu < VXGE_HW_MIN_MTU) || (new_mtu > vpath->max_mtu))
		status = VXGE_HW_ERR_INVALID_MTU_SIZE;

	val64 = readq(&vpath->vp_reg->rxmac_vcfg0);

	val64 &= ~VXGE_HW_RXMAC_VCFG0_RTS_MAX_FRM_LEN(0x3fff);
	val64 |= VXGE_HW_RXMAC_VCFG0_RTS_MAX_FRM_LEN(new_mtu);

	writeq(val64, &vpath->vp_reg->rxmac_vcfg0);

	vpath->vp_config->mtu = new_mtu - VXGE_HW_MAC_HEADER_MAX_SIZE;

exit:
	return status;
}
