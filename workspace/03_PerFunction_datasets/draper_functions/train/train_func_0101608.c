vxge_hw_mrpcim_stats_access(struct __vxge_hw_device *hldev,
			    u32 operation, u32 location, u32 offset, u64 *stat)
{
	u64 val64;
	enum vxge_hw_status status = VXGE_HW_OK;

	status = __vxge_hw_device_is_privilaged(hldev->host_type,
			hldev->func_id);
	if (status != VXGE_HW_OK)
		goto exit;

	val64 = VXGE_HW_XMAC_STATS_SYS_CMD_OP(operation) |
		VXGE_HW_XMAC_STATS_SYS_CMD_STROBE |
		VXGE_HW_XMAC_STATS_SYS_CMD_LOC_SEL(location) |
		VXGE_HW_XMAC_STATS_SYS_CMD_OFFSET_SEL(offset);

	status = __vxge_hw_pio_mem_write64(val64,
				&hldev->mrpcim_reg->xmac_stats_sys_cmd,
				VXGE_HW_XMAC_STATS_SYS_CMD_STROBE,
				hldev->config.device_poll_millis);

	if ((status == VXGE_HW_OK) && (operation == VXGE_HW_STATS_OP_READ))
		*stat = readq(&hldev->mrpcim_reg->xmac_stats_sys_data);
	else
		*stat = 0;
exit:
	return status;
}
