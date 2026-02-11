show_spi_transport_period(struct device *dev,
			  struct device_attribute *attr, char *buf)
{
	struct scsi_target *starget = transport_class_to_starget(dev);
	struct Scsi_Host *shost = dev_to_shost(starget->dev.parent);
	struct spi_internal *i = to_spi_internal(shost->transportt);
	struct spi_transport_attrs *tp =
		(struct spi_transport_attrs *)&starget->starget_data;

	if (i->f->get_period)
		i->f->get_period(starget);

	return show_spi_transport_period_helper(buf, tp->period);
}
