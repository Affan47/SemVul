memstick_device_resume(struct device *dev)
{
	struct memstick_dev *card = container_of(dev, struct memstick_dev,
						  dev);
	struct memstick_driver *drv = container_of(dev->driver,
						   struct memstick_driver,
						   driver);

	if (dev->driver && drv->resume)
		return drv->resume(card);
	return 0;
}
