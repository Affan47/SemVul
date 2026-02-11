coda_psdev_open(struct inode * inode, struct file * file)
{
	struct venus_comm *vcp;
	int idx, err;

	if (task_active_pid_ns(current) != &init_pid_ns)
		return -EINVAL;

	if (current_user_ns() != &init_user_ns)
		return -EINVAL;

	idx = iminor(inode);
	if (idx < 0 || idx >= MAX_CODADEVS)
		return -ENODEV;

	err = -EBUSY;
	vcp = &coda_comms[idx];
	mutex_lock(&vcp->vc_mutex);

	if (!vcp->vc_inuse) {
		vcp->vc_inuse++;

		INIT_LIST_HEAD(&vcp->vc_pending);
		INIT_LIST_HEAD(&vcp->vc_processing);
		init_waitqueue_head(&vcp->vc_waitq);
		vcp->vc_sb = NULL;
		vcp->vc_seq = 0;

		file->private_data = vcp;
		err = 0;
	}

	mutex_unlock(&vcp->vc_mutex);
	return err;
}
