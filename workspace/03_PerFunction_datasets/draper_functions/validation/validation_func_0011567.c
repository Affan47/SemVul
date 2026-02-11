_scsih_set_satl_pending(struct scsi_cmnd *scmd, bool pending)
{
	struct MPT3SAS_DEVICE *priv = scmd->device->hostdata;

	if (scmd->cmnd[0] != ATA_12 && scmd->cmnd[0] != ATA_16)
		return 0;

	if (pending)
		return test_and_set_bit(0, &priv->ata_command_pending);

	clear_bit(0, &priv->ata_command_pending);
	return 0;
}
