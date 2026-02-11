setup_shutdown_watcher(void)
{
	int err;

	err = register_xenbus_watch(&shutdown_watch);
	if (err) {
		pr_err("Failed to set shutdown watcher\n");
		return err;
	}


#ifdef CONFIG_MAGIC_SYSRQ
	err = register_xenbus_watch(&sysrq_watch);
	if (err) {
		pr_err("Failed to set sysrq watcher\n");
		return err;
	}
#endif

	return 0;
}
