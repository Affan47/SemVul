static void start_unregistering(struct ctl_table_header *p)
{


	if (unlikely(p->used)) {
		struct completion wait;
		init_completion(&wait);
		p->unregistering = &wait;
		spin_unlock(&sysctl_lock);
		wait_for_completion(&wait);
	} else {

		p->unregistering = ERR_PTR(-EINVAL);
		spin_unlock(&sysctl_lock);
	}


	proc_sys_prune_dcache(p);


	spin_lock(&sysctl_lock);
	erase_header(p);
}
