bcm2048_sysfs_register_properties(struct bcm2048_device *bdev)
{
	int err = 0;
	int i;

	for (i = 0; i < ARRAY_SIZE(attrs); i++) {
		if (device_create_file(&bdev->client->dev, &attrs[i]) != 0) {
			dev_err(&bdev->client->dev,
					"could not register sysfs entry\n");
			err = -EBUSY;
			bcm2048_sysfs_unregister_properties(bdev, i);
			break;
		}
	}

	return err;
}
