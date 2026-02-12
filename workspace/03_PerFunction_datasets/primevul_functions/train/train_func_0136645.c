perf_event_groups_less(struct perf_event *left, struct perf_event *right)
{
	if (left->cpu < right->cpu)
		return true;
	if (left->cpu > right->cpu)
		return false;

#ifdef CONFIG_CGROUP_PERF
	if (left->cgrp != right->cgrp) {
		if (!left->cgrp || !left->cgrp->css.cgroup) {


			return true;
		}
		if (!right->cgrp || !right->cgrp->css.cgroup) {


			return false;
		}

		if (left->cgrp->css.cgroup->kn->id < right->cgrp->css.cgroup->kn->id)
			return true;

		return false;
	}
#endif

	if (left->group_index < right->group_index)
		return true;
	if (left->group_index > right->group_index)
		return false;

	return false;
}
