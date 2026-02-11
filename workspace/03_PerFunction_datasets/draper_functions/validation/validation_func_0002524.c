ips_biosparam(struct scsi_device *sdev, struct block_device *bdev,
			 sector_t capacity, int geom[])
{
	ips_ha_t *ha = (ips_ha_t *) sdev->host->hostdata;
	int heads;
	int sectors;
	int cylinders;

	METHOD_TRACE("ips_biosparam", 1);

	if (!ha)

		return (0);

	if (!ha->active)
		return (0);

	if (!ips_read_adapter_status(ha, IPS_INTR_ON))

		return (0);

	if ((capacity > 0x400000) && ((ha->enq->ucMiscFlag & 0x8) == 0)) {
		heads = IPS_NORM_HEADS;
		sectors = IPS_NORM_SECTORS;
	} else {
		heads = IPS_COMP_HEADS;
		sectors = IPS_COMP_SECTORS;
	}

	cylinders = (unsigned long) capacity / (heads * sectors);

	DEBUG_VAR(2, "Geometry: heads: %d, sectors: %d, cylinders: %d",
		  heads, sectors, cylinders);

	geom[0] = heads;
	geom[1] = sectors;
	geom[2] = cylinders;

	return (0);
}
