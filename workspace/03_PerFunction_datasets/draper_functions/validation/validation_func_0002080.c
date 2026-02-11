us5182d_probe(struct i2c_client *client,
			 const struct i2c_device_id *id)
{
	struct us5182d_data *data;
	struct iio_dev *indio_dev;
	int ret;

	indio_dev = devm_iio_device_alloc(&client->dev, sizeof(*data));
	if (!indio_dev)
		return -ENOMEM;

	data = iio_priv(indio_dev);
	i2c_set_clientdata(client, indio_dev);
	data->client = client;

	mutex_init(&data->lock);

	indio_dev->dev.parent = &client->dev;
	indio_dev->info = &us5182d_info;
	indio_dev->name = US5182D_DRV_NAME;
	indio_dev->channels = us5182d_channels;
	indio_dev->num_channels = ARRAY_SIZE(us5182d_channels);
	indio_dev->modes = INDIO_DIRECT_MODE;

	ret = i2c_smbus_read_byte_data(data->client, US5182D_REG_CHIPID);
	if (ret != US5182D_CHIPID) {
		dev_err(&data->client->dev,
			"Failed to detect US5182 light chip\n");
		return (ret < 0) ? ret : -ENODEV;
	}

	us5182d_get_platform_data(indio_dev);
	ret = us5182d_init(indio_dev);
	if (ret < 0)
		return ret;

	ret = us5182d_dark_gain_config(indio_dev);
	if (ret < 0)
		return ret;

	return iio_device_register(indio_dev);
}
