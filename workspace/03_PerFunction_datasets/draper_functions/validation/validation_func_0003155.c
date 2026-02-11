anysee_add_i2c_dev(struct dvb_usb_device *d, const char *type,
		u8 addr, void *platform_data)
{
	int ret, num;
	struct anysee_state *state = d_to_priv(d);
	struct i2c_client *client;
	struct i2c_adapter *adapter = &d->i2c_adap;
	struct i2c_board_info board_info = {
		.addr = addr,
		.platform_data = platform_data,
	};

	strlcpy(board_info.type, type, I2C_NAME_SIZE);


	for (num = 0; num < ANYSEE_I2C_CLIENT_MAX; num++) {
		if (state->i2c_client[num] == NULL)
			break;
	}

	dev_dbg(&d->udev->dev, "%s: num=%d\n", __func__, num);

	if (num == ANYSEE_I2C_CLIENT_MAX) {
		dev_err(&d->udev->dev, "%s: I2C client out of index\n",
				KBUILD_MODNAME);
		ret = -ENODEV;
		goto err;
	}

	request_module("%s", board_info.type);


	client = i2c_new_device(adapter, &board_info);
	if (client == NULL || client->dev.driver == NULL) {
		ret = -ENODEV;
		goto err;
	}


	if (!try_module_get(client->dev.driver->owner)) {
		i2c_unregister_device(client);
		ret = -ENODEV;
		goto err;
	}

	state->i2c_client[num] = client;
	return 0;
err:
	dev_dbg(&d->udev->dev, "%s: failed=%d\n", __func__, ret);
	return ret;
}
