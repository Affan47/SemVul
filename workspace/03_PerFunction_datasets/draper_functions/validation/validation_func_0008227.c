brasero_scsi_command_new (const BraseroScsiCmdInfo *info,
			  BraseroDeviceHandle *handle)
{
	BraseroScsiCmd *cmd;

	g_return_val_if_fail (handle != NULL, NULL);


	cmd = g_new0 (BraseroScsiCmd, 1);
	cmd->info = info;
	cmd->handle = handle;

	BRASERO_SCSI_CMD_SET_OPCODE (cmd);
	return cmd;
}
