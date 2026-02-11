set_addressing(ide_drive_t *drive, int arg)
{
	if (arg < 0 || arg > 2)
		return -EINVAL;

	if (arg && ((drive->hwif->host_flags & IDE_HFLAG_NO_LBA48) ||
	    ata_id_lba48_enabled(drive->id) == 0))
		return -EIO;

	if (arg == 2)
		arg = 0;

	if (arg)
		drive->dev_flags |= IDE_DFLAG_LBA48;
	else
		drive->dev_flags &= ~IDE_DFLAG_LBA48;

	return 0;
}
