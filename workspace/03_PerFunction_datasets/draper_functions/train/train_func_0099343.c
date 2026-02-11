xen_late_init_mcelog(void)
{
	int ret;


	if (!xen_initial_domain())
		return -ENODEV;


	ret = misc_register(&xen_mce_chrdev_device);
	if (ret)
		return ret;

	ret = bind_virq_for_mce();
	if (ret)
		goto deregister;

	return 0;

deregister:
	misc_deregister(&xen_mce_chrdev_device);
	return ret;
}
