it821x_dma_start(ide_drive_t *drive)
{
	ide_hwif_t *hwif = drive->hwif;
	struct it821x_dev *itdev = ide_get_hwifdata(hwif);
	u8 unit = drive->dn & 1;

	if(itdev->mwdma[unit] != MWDMA_OFF)
		it821x_program(drive, itdev->mwdma[unit]);
	else if(itdev->udma[unit] != UDMA_OFF && itdev->timing10)
		it821x_program_udma(drive, itdev->udma[unit]);
	ide_dma_start(drive);
}
