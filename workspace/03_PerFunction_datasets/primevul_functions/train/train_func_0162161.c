static int pcan_usb_fd_set_bus(struct peak_usb_device *dev, u8 onoff)
{
	u8 *pc = pcan_usb_fd_cmd_buffer(dev);
	int l;

	if (onoff) {

		l = pcan_usb_fd_build_restart_cmd(dev, pc);
	} else {
		struct pucan_command *cmd = (struct pucan_command *)pc;


		cmd->opcode_channel = pucan_cmd_opcode_channel(dev->ctrl_idx,
							PUCAN_CMD_RESET_MODE);
		l = sizeof(struct pucan_command);
	}


	return pcan_usb_fd_send_cmd(dev, pc + l);
}
