legacy_set_mode(struct ata_link *link, struct ata_device **unused)
{
	struct ata_device *dev;

	ata_for_each_dev(dev, link, ENABLED) {
		ata_dev_info(dev, "configured for PIO\n");
		dev->pio_mode = XFER_PIO_0;
		dev->xfer_mode = XFER_PIO_0;
		dev->xfer_shift = ATA_SHIFT_PIO;
		dev->flags |= ATA_DFLAG_PIO;
	}
	return 0;
}
