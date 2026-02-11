watchdog_unregister_device(struct watchdog_device *wdd)
{
	mutex_lock(&wtd_deferred_reg_mutex);
	if (wtd_deferred_reg_done)
		__watchdog_unregister_device(wdd);
	else
		watchdog_deferred_registration_del(wdd);
	mutex_unlock(&wtd_deferred_reg_mutex);
}
