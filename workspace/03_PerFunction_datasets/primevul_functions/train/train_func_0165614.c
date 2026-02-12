static int inotify_release(struct inode *ignored, struct file *file)
{
	struct inotify_device *dev = file->private_data;

	inotify_destroy(dev->ih);


	mutex_lock(&dev->ev_mutex);
	while (!list_empty(&dev->events))
		inotify_dev_event_dequeue(dev);
	mutex_unlock(&dev->ev_mutex);


	put_inotify_dev(dev);

	return 0;
}
