static int do_rebind(char *busid, struct bus_id_priv *busid_priv)
{
	int ret;


	if (busid_priv->udev->dev.parent)
		device_lock(busid_priv->udev->dev.parent);
	ret = device_attach(&busid_priv->udev->dev);
	if (busid_priv->udev->dev.parent)
		device_unlock(busid_priv->udev->dev.parent);
	if (ret < 0) {
		dev_err(&busid_priv->udev->dev, "rebind failed\n");
		return ret;
	}
	return 0;
}
