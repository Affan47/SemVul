cgroup_pidlist_start(struct seq_file *s, loff_t *pos)
{


	struct kernfs_open_file *of = s->private;
	struct cgroup *cgrp = seq_css(s)->cgroup;
	struct cgroup_pidlist *l;
	enum cgroup_filetype type = seq_cft(s)->private;
	int index = 0, pid = *pos;
	int *iter, ret;

	mutex_lock(&cgrp->pidlist_mutex);


	if (of->priv)
		of->priv = cgroup_pidlist_find(cgrp, type);


	if (!of->priv) {
		ret = pidlist_array_load(cgrp, type,
					 (struct cgroup_pidlist **)&of->priv);
		if (ret)
			return ERR_PTR(ret);
	}
	l = of->priv;

	if (pid) {
		int end = l->length;

		while (index < end) {
			int mid = (index + end) / 2;
			if (cgroup_pid_fry(cgrp, l->list[mid]) == pid) {
				index = mid;
				break;
			} else if (cgroup_pid_fry(cgrp, l->list[mid]) <= pid)
				index = mid + 1;
			else
				end = mid;
		}
	}

	if (index >= l->length)
		return NULL;

	iter = l->list + index;
	*pos = cgroup_pid_fry(cgrp, *iter);
	return iter;
}
