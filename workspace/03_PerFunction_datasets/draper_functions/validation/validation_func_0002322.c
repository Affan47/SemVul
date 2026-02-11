cm3232_probe(struct i2c_client *client,
			const struct i2c_device_id *id)
{
	struct cm3232_chip *chip;
	struct iio_dev *indio_dev;
	int ret;

	indio_dev = devm_iio_device_alloc(&client->dev, sizeof(*chip));
	if (!indio_dev)
		return -ENOMEM;

	chip = iio_priv(indio_dev);
	i2c_set_clientdata(client, indio_dev);
	chip->client = client;

	indio_dev->dev.parent = &client->dev;
	indio_dev->channels = cm3232_channels;
	indio_dev->num_channels = ARRAY_SIZE(cm3232_channels);
	indio_dev->info = &cm3232_info;
	indio_dev->name = id->name;
	indio_dev->modes = INDIO_DIRECT_MODE;

	ret = cm3232_reg_init(chip);
	if (ret) {
		dev_err(&client->dev,
			"%s: register init failed\n",
			__func__);
		return ret;
	}

	return iio_device_register(indio_dev);
}
