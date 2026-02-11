sata_pmp_detach(struct ata_device *dev)
{
	struct ata_link *link = dev->link;
	struct ata_port *ap = link->ap;
	struct ata_link *tlink;
	unsigned long flags;

	ata_dev_info(dev, "Port Multiplier detaching\n");

	WARN_ON(!ata_is_host_link(link) || dev->devno ||
		link->pmp != SATA_PMP_CTRL_PORT);

	if (ap->ops->pmp_detach)
		ap->ops->pmp_detach(ap);

	ata_for_each_link(tlink, ap, EDGE)
		ata_eh_detach_dev(tlink->device);

	spin_lock_irqsave(ap->lock, flags);
	ap->nr_pmp_links = 0;
	link->pmp = 0;
	spin_unlock_irqrestore(ap->lock, flags);
}
