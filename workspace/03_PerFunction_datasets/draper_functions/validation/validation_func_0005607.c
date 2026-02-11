bcm2048_get_rds_data(struct bcm2048_device *bdev, char *data)
{
	int err = 0, i, p = 0;
	char *data_buffer;

	mutex_lock(&bdev->mutex);

	if (!bdev->rds_info.text_len) {
		err = -EINVAL;
		goto unlock;
	}

	data_buffer = kcalloc(BCM2048_MAX_RDS_RADIO_TEXT, 5, GFP_KERNEL);
	if (!data_buffer) {
		err = -ENOMEM;
		goto unlock;
	}

	for (i = 0; i < bdev->rds_info.text_len; i++) {
		p += sprintf(data_buffer+p, "%x ",
			bdev->rds_info.radio_text[i]);
	}

	memcpy(data, data_buffer, p);
	kfree(data_buffer);

unlock:
	mutex_unlock(&bdev->mutex);
	return err;
}
