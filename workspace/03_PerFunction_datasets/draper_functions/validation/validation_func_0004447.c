iio_device_unregister(struct iio_dev *indio_dev)
{
	mutex_lock(&indio_dev->info_exist_lock);

	device_del(&indio_dev->dev);

	if (indio_dev->chrdev.dev)
		cdev_del(&indio_dev->chrdev);
	iio_device_unregister_debugfs(indio_dev);

	iio_disable_all_buffers(indio_dev);

	indio_dev->info = NULL;

	iio_device_wakeup_eventset(indio_dev);
	iio_buffer_wakeup_poll(indio_dev);

	mutex_unlock(&indio_dev->info_exist_lock);

	iio_buffer_free_sysfs_and_mask(indio_dev);
}
