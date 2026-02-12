static int rtsx_usb_ms_suspend(struct device *dev)
{
	struct rtsx_usb_ms *host = dev_get_drvdata(dev);
	struct memstick_host *msh = host->msh;


	host->system_suspending = true;
	memstick_suspend_host(msh);

	return 0;
}
