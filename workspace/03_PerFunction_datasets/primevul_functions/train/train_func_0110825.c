int selinux_disable(void)
{
	if (ss_initialized) {

		return -EINVAL;
	}

	if (selinux_disabled) {

		return -EINVAL;
	}

	printk(KERN_INFO "SELinux:  Disabled at runtime.\n");

	selinux_disabled = 1;
	selinux_enabled = 0;

	security_delete_hooks(selinux_hooks, ARRAY_SIZE(selinux_hooks));


	avc_disable();


	selinux_nf_ip_exit();


	exit_sel_fs();

	return 0;
}
