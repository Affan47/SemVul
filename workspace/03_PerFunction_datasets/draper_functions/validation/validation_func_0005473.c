snd_ctl_elem_list_alloc_space(snd_ctl_elem_list_t *obj, unsigned int entries)
{
	free(obj->pids);
	obj->pids = calloc(entries, sizeof(*obj->pids));
	if (!obj->pids) {
		obj->space = 0;
		return -ENOMEM;
	}
	obj->space = entries;
	return 0;
}
