vfio_bus_type(struct device *dev, void *data)
{
	struct bus_type **bus = data;

	if (*bus && *bus != dev->bus)
		return -EINVAL;

	*bus = dev->bus;

	return 0;
}
