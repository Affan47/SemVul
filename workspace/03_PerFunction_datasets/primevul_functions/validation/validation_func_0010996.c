void input_close_device(struct input_handle *handle)
{
	struct input_dev *dev = handle->dev;

	mutex_lock(&dev->mutex);

	__input_release_device(handle);

	if (!--dev->users) {
		if (dev->poller)
			input_dev_poller_stop(dev->poller);

		if (dev->close)
			dev->close(dev);
	}

	if (!--handle->open) {


		synchronize_rcu();
	}

	mutex_unlock(&dev->mutex);
}
