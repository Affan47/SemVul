hid_magn_3d_probe(struct platform_device *pdev)
{
	int ret = 0;
	static char *name = "magn_3d";
	struct iio_dev *indio_dev;
	struct magn_3d_state *magn_state;
	struct hid_sensor_hub_device *hsdev = pdev->dev.platform_data;
	struct iio_chan_spec *channels;
	int chan_count = 0;

	indio_dev = devm_iio_device_alloc(&pdev->dev,
					  sizeof(struct magn_3d_state));
	if (indio_dev == NULL)
		return -ENOMEM;

	platform_set_drvdata(pdev, indio_dev);

	magn_state = iio_priv(indio_dev);
	magn_state->common_attributes.hsdev = hsdev;
	magn_state->common_attributes.pdev = pdev;

	ret = hid_sensor_parse_common_attributes(hsdev,
				HID_USAGE_SENSOR_COMPASS_3D,
				&magn_state->common_attributes);
	if (ret) {
		dev_err(&pdev->dev, "failed to setup common attributes\n");
		return ret;
	}

	ret = magn_3d_parse_report(pdev, hsdev,
				&channels, &chan_count,
				HID_USAGE_SENSOR_COMPASS_3D, magn_state);
	if (ret) {
		dev_err(&pdev->dev, "failed to parse report\n");
		return ret;
	}

	indio_dev->channels = channels;
	indio_dev->num_channels = chan_count;
	indio_dev->dev.parent = &pdev->dev;
	indio_dev->info = &magn_3d_info;
	indio_dev->name = name;
	indio_dev->modes = INDIO_DIRECT_MODE;

	ret = iio_triggered_buffer_setup(indio_dev, &iio_pollfunc_store_time,
		NULL, NULL);
	if (ret) {
		dev_err(&pdev->dev, "failed to initialize trigger buffer\n");
		return ret;
	}
	atomic_set(&magn_state->common_attributes.data_ready, 0);
	ret = hid_sensor_setup_trigger(indio_dev, name,
					&magn_state->common_attributes);
	if (ret < 0) {
		dev_err(&pdev->dev, "trigger setup failed\n");
		goto error_unreg_buffer_funcs;
	}

	ret = iio_device_register(indio_dev);
	if (ret) {
		dev_err(&pdev->dev, "device register failed\n");
		goto error_remove_trigger;
	}

	magn_state->callbacks.send_event = magn_3d_proc_event;
	magn_state->callbacks.capture_sample = magn_3d_capture_sample;
	magn_state->callbacks.pdev = pdev;
	ret = sensor_hub_register_callback(hsdev, HID_USAGE_SENSOR_COMPASS_3D,
					&magn_state->callbacks);
	if (ret < 0) {
		dev_err(&pdev->dev, "callback reg failed\n");
		goto error_iio_unreg;
	}

	return ret;

error_iio_unreg:
	iio_device_unregister(indio_dev);
error_remove_trigger:
	hid_sensor_remove_trigger(&magn_state->common_attributes);
error_unreg_buffer_funcs:
	iio_triggered_buffer_cleanup(indio_dev);
	return ret;
}
