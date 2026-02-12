static int pcan_usb_fd_set_filter_std(struct peak_usb_device *dev, int idx,
				      u32 mask)
{
	struct pucan_filter_std *cmd = pcan_usb_fd_cmd_buffer(dev);
	int i, n;


	if ((idx < 0) || (idx >= (1 << PUCAN_FLTSTD_ROW_IDX_BITS))) {
		n = 1 << PUCAN_FLTSTD_ROW_IDX_BITS;
		idx = 0;


	} else {
		n = idx + 1;
	}

	for (i = idx; i < n; i++, cmd++) {
		cmd->opcode_channel = pucan_cmd_opcode_channel(dev->ctrl_idx,
							PUCAN_CMD_FILTER_STD);
		cmd->idx = cpu_to_le16(i);
		cmd->mask = cpu_to_le32(mask);
	}


	return pcan_usb_fd_send_cmd(dev, cmd);
}
