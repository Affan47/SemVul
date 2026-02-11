command_phase1(struct AdapterCtlBlk *acb, struct ScsiReqBlk *srb,
		u16 *pscsi_status)
{
	struct DeviceCtlBlk *dcb;
	u8 *ptr;
	u16 i;
	dprintkdbg(DBG_0, "command_phase1: (0x%p)\n", srb->cmd);

	clear_fifo(acb, "command_phase1");
	DC395x_write16(acb, TRM_S1040_SCSI_CONTROL, DO_CLRATN);
	if (!(srb->flag & AUTO_REQSENSE)) {
		ptr = (u8 *)srb->cmd->cmnd;
		for (i = 0; i < srb->cmd->cmd_len; i++) {
			DC395x_write8(acb, TRM_S1040_SCSI_FIFO, *ptr);
			ptr++;
		}
	} else {
		DC395x_write8(acb, TRM_S1040_SCSI_FIFO, REQUEST_SENSE);
		dcb = acb->active_dcb;

		DC395x_write8(acb, TRM_S1040_SCSI_FIFO, (dcb->target_lun << 5));
		DC395x_write8(acb, TRM_S1040_SCSI_FIFO, 0);
		DC395x_write8(acb, TRM_S1040_SCSI_FIFO, 0);
		DC395x_write8(acb, TRM_S1040_SCSI_FIFO, SCSI_SENSE_BUFFERSIZE);
		DC395x_write8(acb, TRM_S1040_SCSI_FIFO, 0);
	}
	srb->state |= SRB_COMMAND;

	DC395x_write16(acb, TRM_S1040_SCSI_CONTROL, DO_DATALATCH);

	DC395x_write8(acb, TRM_S1040_SCSI_COMMAND, SCMD_FIFO_OUT);
}
