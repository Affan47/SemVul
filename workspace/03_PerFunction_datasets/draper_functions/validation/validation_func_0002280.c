cmd64x_set_pio_mode(ide_hwif_t *hwif, ide_drive_t *drive)
{
	const u8 pio = drive->pio_mode - XFER_PIO_0;


	if (pio == 8 || pio == 9)
		return;

	cmd64x_program_timings(drive, XFER_PIO_0 + pio);
}
