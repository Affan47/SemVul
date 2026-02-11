asd_set_ddb_type(struct domain_device *dev)
{
	struct asd_ha_struct *asd_ha = dev->port->ha->lldd_ha;
	int ddb = (int) (unsigned long) dev->lldd_dev;

	if (dev->dev_type == SAS_SATA_PM_PORT)
		asd_ddbsite_write_byte(asd_ha,ddb, DDB_TYPE, DDB_TYPE_PM_PORT);
	else if (dev->tproto)
		asd_ddbsite_write_byte(asd_ha,ddb, DDB_TYPE, DDB_TYPE_TARGET);
	else
		asd_ddbsite_write_byte(asd_ha,ddb,DDB_TYPE,DDB_TYPE_INITIATOR);
}
