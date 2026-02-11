sas_host_setup(struct transport_container *tc, struct device *dev,
			  struct device *cdev)
{
	struct Scsi_Host *shost = dev_to_shost(dev);
	struct sas_host_attrs *sas_host = to_sas_host_attrs(shost);

	INIT_LIST_HEAD(&sas_host->rphy_list);
	mutex_init(&sas_host->lock);
	sas_host->next_target_id = 0;
	sas_host->next_expander_id = 0;
	sas_host->next_port_id = 0;

	if (sas_bsg_initialize(shost, NULL))
		dev_printk(KERN_ERR, dev, "fail to a bsg device %d\n",
			   shost->host_no);

	return 0;
}
