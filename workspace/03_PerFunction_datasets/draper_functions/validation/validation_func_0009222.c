nx_get_fw_offs(struct netxen_adapter *adapter)
{
	u32 offs = NETXEN_IMAGE_START;

	if (adapter->fw_type == NX_UNIFIED_ROMIMAGE)
		offs = cpu_to_le32((nx_get_data_desc(adapter,
					NX_UNI_DIR_SECT_FW,
					NX_UNI_FIRMWARE_IDX_OFF))->findex);

	return (u8 *)&adapter->fw->data[offs];
}
