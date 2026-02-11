mic_poll(struct file *f, poll_table *wait)
{
	struct mic_vdev *mvdev = (struct mic_vdev *)f->private_data;
	int mask = 0;

	poll_wait(f, &mvdev->waitq, wait);

	if (mic_vdev_inited(mvdev)) {
		mask = POLLERR;
	} else if (mvdev->poll_wake) {
		mvdev->poll_wake = 0;
		mask = POLLIN | POLLOUT;
	}

	return mask;
}
