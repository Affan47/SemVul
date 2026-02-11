mem_cgroup_hierarchy_write(struct cgroup_subsys_state *css,
				      struct cftype *cft, u64 val)
{
	int retval = 0;
	struct mem_cgroup *memcg = mem_cgroup_from_css(css);
	struct mem_cgroup *parent_memcg = mem_cgroup_from_css(memcg->css.parent);

	mutex_lock(&memcg_create_mutex);

	if (memcg->use_hierarchy == val)
		goto out;


	if ((!parent_memcg || !parent_memcg->use_hierarchy) &&
				(val == 1 || val == 0)) {
		if (!memcg_has_children(memcg))
			memcg->use_hierarchy = val;
		else
			retval = -EBUSY;
	} else
		retval = -EINVAL;

out:
	mutex_unlock(&memcg_create_mutex);

	return retval;
}
