usb_autopm_get_interface(struct usb_interface *intf)
{
	int	status;

	status = pm_runtime_get_sync(&intf->dev);
	if (status < 0)
		pm_runtime_put_sync(&intf->dev);
	else
		atomic_inc(&intf->pm_usage_cnt);
	dev_vdbg(&intf->dev, "%s: cnt %d -> %d\n",
			__func__, atomic_read(&intf->dev.power.usage_count),
			status);
	if (status > 0)
		status = 0;
	return status;
}
