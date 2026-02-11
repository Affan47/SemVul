AscInitGetConfig(struct Scsi_Host *shost)
{
	struct asc_board *board = shost_priv(shost);
	ASC_DVC_VAR *asc_dvc = &board->dvc_var.asc_dvc_var;
	unsigned short warn_code = 0;

	asc_dvc->init_state = ASC_INIT_STATE_BEG_GET_CFG;
	if (asc_dvc->err_code != 0)
		return asc_dvc->err_code;

	if (AscFindSignature(asc_dvc->iop_base)) {
		AscInitAscDvcVar(asc_dvc);
		warn_code = AscInitFromEEP(asc_dvc);
		asc_dvc->init_state |= ASC_INIT_STATE_END_GET_CFG;
		if (asc_dvc->scsi_reset_wait > ASC_MAX_SCSI_RESET_WAIT)
			asc_dvc->scsi_reset_wait = ASC_MAX_SCSI_RESET_WAIT;
	} else {
		asc_dvc->err_code = ASC_IERR_BAD_SIGNATURE;
	}

	switch (warn_code) {
	case 0:
		break;
	case ASC_WARN_IO_PORT_ROTATE:
		shost_printk(KERN_WARNING, shost, "I/O port address "
				"modified\n");
		break;
	case ASC_WARN_AUTO_CONFIG:
		shost_printk(KERN_WARNING, shost, "I/O port increment switch "
				"enabled\n");
		break;
	case ASC_WARN_EEPROM_CHKSUM:
		shost_printk(KERN_WARNING, shost, "EEPROM checksum error\n");
		break;
	case ASC_WARN_IRQ_MODIFIED:
		shost_printk(KERN_WARNING, shost, "IRQ modified\n");
		break;
	case ASC_WARN_CMD_QNG_CONFLICT:
		shost_printk(KERN_WARNING, shost, "tag queuing enabled w/o "
				"disconnects\n");
		break;
	default:
		shost_printk(KERN_WARNING, shost, "unknown warning: 0x%x\n",
				warn_code);
		break;
	}

	if (asc_dvc->err_code != 0)
		shost_printk(KERN_ERR, shost, "error 0x%x at init_state "
			"0x%x\n", asc_dvc->err_code, asc_dvc->init_state);

	return asc_dvc->err_code;
}
