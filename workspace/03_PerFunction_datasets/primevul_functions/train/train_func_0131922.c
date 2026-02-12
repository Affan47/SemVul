static void evdev_cleanup(struct evdev *evdev)
{
	struct input_handle *handle = &evdev->handle;

	evdev_mark_dead(evdev);
	evdev_hangup(evdev);

	cdev_del(&evdev->cdev);


	if (evdev->open) {
		input_flush_device(handle, NULL);
		input_close_device(handle);
	}
}
