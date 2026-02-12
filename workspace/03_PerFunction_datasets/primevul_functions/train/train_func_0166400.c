int __init addrconf_init(void)
{
	int err = 0;


	rtnl_lock();
	if (!ipv6_add_dev(&loopback_dev))
		err = -ENOMEM;
	rtnl_unlock();
	if (err)
		return err;

	register_netdevice_notifier(&ipv6_dev_notf);

#ifdef CONFIG_IPV6_PRIVACY
	md5_tfm = crypto_alloc_tfm("md5", 0);
	if (unlikely(md5_tfm == NULL))
		printk(KERN_WARNING
			"failed to load transform for md5\n");
#endif

	addrconf_verify(0);
	rtnetlink_links[PF_INET6] = inet6_rtnetlink_table;
#ifdef CONFIG_SYSCTL
	addrconf_sysctl.sysctl_header =
		register_sysctl_table(addrconf_sysctl.addrconf_root_dir, 0);
	addrconf_sysctl_register(NULL, &ipv6_devconf_dflt);
#endif

	return 0;
}
