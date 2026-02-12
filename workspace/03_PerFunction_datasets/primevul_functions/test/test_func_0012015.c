int selinux_disable(struct selinux_state *state)
{
	if (selinux_initialized(state)) {

		return -EINVAL;
	}

	if (selinux_disabled(state)) {

		return -EINVAL;
	}

	selinux_mark_disabled(state);

	pr_info("SELinux:  Disabled at runtime.\n");


	selinux_nf_ip_exit();

	security_delete_hooks(selinux_hooks, ARRAY_SIZE(selinux_hooks));


	avc_disable();


	exit_sel_fs();

	return 0;
}
