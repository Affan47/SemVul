snd_ctl_shm_elem_list(snd_ctl_t *ctl, snd_ctl_elem_list_t *list)
{
	snd_ctl_shm_t *shm = ctl->private_data;
	volatile snd_ctl_shm_ctrl_t *ctrl = shm->ctrl;
	size_t maxsize = CTL_SHM_DATA_MAXLEN;
	size_t bytes = list->space * sizeof(*list->pids);
	int err;
	snd_ctl_elem_id_t *pids = list->pids;
	if (bytes > maxsize)
		return -EINVAL;
	ctrl->u.element_list = *list;
	ctrl->cmd = SNDRV_CTL_IOCTL_ELEM_LIST;
	err = snd_ctl_shm_action(ctl);
	if (err < 0)
		return err;
	*list = ctrl->u.element_list;
	list->pids = pids;
	bytes = list->used * sizeof(*list->pids);
	memcpy(pids, (void *)ctrl->data, bytes);
	return err;
}
