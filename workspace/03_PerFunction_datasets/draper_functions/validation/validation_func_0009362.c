iTCO_wdt_suspend_noirq(struct device *dev)
{
	int ret = 0;

	iTCO_wdt_private.suspended = false;
	if (watchdog_active(&iTCO_wdt_watchdog_dev) && need_suspend()) {
		ret = iTCO_wdt_stop(&iTCO_wdt_watchdog_dev);
		if (!ret)
			iTCO_wdt_private.suspended = true;
	}
	return ret;
}
