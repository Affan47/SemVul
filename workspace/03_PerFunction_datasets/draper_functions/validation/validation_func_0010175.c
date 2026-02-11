pch_vbus_gpio_get_value(struct pch_udc_dev *dev)
{
	int vbus = 0;

	if (dev->vbus_gpio.port)
		vbus = gpio_get_value(dev->vbus_gpio.port) ? 1 : 0;
	else
		vbus = -1;

	return vbus;
}
