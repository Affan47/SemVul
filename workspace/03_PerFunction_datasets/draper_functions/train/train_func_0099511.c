iio_device_register(struct iio_dev *indio_dev)
{
	int ret;


	if (!indio_dev->dev.of_node && indio_dev->dev.parent)
		indio_dev->dev.of_node = indio_dev->dev.parent->of_node;

	ret = iio_check_unique_scan_index(indio_dev);
	if (ret < 0)
		return ret;


	indio_dev->dev.devt = MKDEV(MAJOR(iio_devt), indio_dev->id);

	ret = iio_device_register_debugfs(indio_dev);
	if (ret) {
		dev_err(indio_dev->dev.parent,
			"Failed to register debugfs interfaces\n");
		return ret;
	}

	ret = iio_buffer_alloc_sysfs_and_mask(indio_dev);
	if (ret) {
		dev_err(indio_dev->dev.parent,
			"Failed to create buffer sysfs interfaces\n");
		goto error_unreg_debugfs;
	}

	ret = iio_device_register_sysfs(indio_dev);
	if (ret) {
		dev_err(indio_dev->dev.parent,
			"Failed to register sysfs interfaces\n");
		goto error_buffer_free_sysfs;
	}
	ret = iio_device_register_eventset(indio_dev);
	if (ret) {
		dev_err(indio_dev->dev.parent,
			"Failed to register event set\n");
		goto error_free_sysfs;
	}
	if (indio_dev->modes & (INDIO_BUFFER_TRIGGERED | INDIO_EVENT_TRIGGERED))
		iio_device_register_trigger_consumer(indio_dev);

	if ((indio_dev->modes & INDIO_ALL_BUFFER_MODES) &&
		indio_dev->setup_ops == NULL)
		indio_dev->setup_ops = &noop_ring_setup_ops;

	cdev_init(&indio_dev->chrdev, &iio_buffer_fileops);
	indio_dev->chrdev.owner = indio_dev->info->driver_module;
	indio_dev->chrdev.kobj.parent = &indio_dev->dev.kobj;
	ret = cdev_add(&indio_dev->chrdev, indio_dev->dev.devt, 1);
	if (ret < 0)
		goto error_unreg_eventset;

	ret = device_add(&indio_dev->dev);
	if (ret < 0)
		goto error_cdev_del;

	return 0;
error_cdev_del:
	cdev_del(&indio_dev->chrdev);
error_unreg_eventset:
	iio_device_unregister_eventset(indio_dev);
error_free_sysfs:
	iio_device_unregister_sysfs(indio_dev);
error_buffer_free_sysfs:
	iio_buffer_free_sysfs_and_mask(indio_dev);
error_unreg_debugfs:
	iio_device_unregister_debugfs(indio_dev);
	return ret;
}
