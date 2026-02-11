as102_start_stream(struct as102_dev_t *dev)
{
	struct as10x_bus_adapter_t *bus_adap;
	int ret = -EFAULT;

	if (dev != NULL)
		bus_adap = &dev->bus_adap;
	else
		return ret;

	if (bus_adap->ops->start_stream != NULL)
		ret = bus_adap->ops->start_stream(dev);

	if (ts_auto_disable) {
		if (mutex_lock_interruptible(&dev->bus_adap.lock))
			return -EFAULT;

		ret = as10x_cmd_start_streaming(bus_adap);

		mutex_unlock(&dev->bus_adap.lock);
	}

	return ret;
}
