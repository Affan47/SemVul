cgroup_init_subsys(struct cgroup_subsys *ss, bool early)
{
	struct cgroup_subsys_state *css;

	printk(KERN_INFO "Initializing cgroup subsys %s\n", ss->name);

	mutex_lock(&cgroup_mutex);

	idr_init(&ss->css_idr);
	INIT_LIST_HEAD(&ss->cfts);


	ss->root = &cgrp_dfl_root;
	css = ss->css_alloc(cgroup_css(&cgrp_dfl_root.cgrp, ss));

	BUG_ON(IS_ERR(css));
	init_and_link_css(css, ss, &cgrp_dfl_root.cgrp);


	css->flags |= CSS_NO_REF;

	if (early) {

		css->id = 1;
	} else {
		css->id = cgroup_idr_alloc(&ss->css_idr, css, 1, 2, GFP_KERNEL);
		BUG_ON(css->id < 0);
	}


	init_css_set.subsys[ss->id] = css;

	have_fork_callback |= (bool)ss->fork << ss->id;
	have_exit_callback |= (bool)ss->exit << ss->id;
	have_free_callback |= (bool)ss->free << ss->id;
	have_canfork_callback |= (bool)ss->can_fork << ss->id;


	BUG_ON(!list_empty(&init_task.tasks));

	BUG_ON(online_css(css));

	mutex_unlock(&cgroup_mutex);
}
