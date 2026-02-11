ipmi_unregister_watchdog(int ipmi_intf)
{
	int rv;

	if (!watchdog_user)
		goto out;

	if (watchdog_ifnum != ipmi_intf)
		goto out;


	misc_deregister(&ipmi_wdog_miscdev);


	while (atomic_read(&set_timeout_tofree))
		schedule_timeout_uninterruptible(1);


	rv = ipmi_destroy_user(watchdog_user);
	if (rv) {
		printk(KERN_WARNING PFX "error unlinking from IPMI: %d\n",
		       rv);
	}
	watchdog_user = NULL;

 out:
	return;
}
