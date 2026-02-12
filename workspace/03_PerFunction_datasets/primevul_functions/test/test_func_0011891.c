static int selinux_task_setrlimit(struct task_struct *p, unsigned int resource,
		struct rlimit *new_rlim)
{
	struct rlimit *old_rlim = p->signal->rlim + resource;


	if (old_rlim->rlim_max != new_rlim->rlim_max)
		return avc_has_perm(&selinux_state,
				    current_sid(), task_sid_obj(p),
				    SECCLASS_PROCESS, PROCESS__SETRLIMIT, NULL);

	return 0;
}
