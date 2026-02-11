do_sas_phy_delete(struct device *dev, void *data)
{
	int pass = (int)(unsigned long)data;

	if (pass == 0 && scsi_is_sas_port(dev))
		sas_port_delete(dev_to_sas_port(dev));
	else if (pass == 1 && scsi_is_sas_phy(dev))
		sas_phy_delete(dev_to_phy(dev));
	return 0;
}
