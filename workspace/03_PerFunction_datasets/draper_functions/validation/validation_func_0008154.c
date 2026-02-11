ak881x_probe(struct i2c_client *client,
			const struct i2c_device_id *did)
{
	struct i2c_adapter *adapter = to_i2c_adapter(client->dev.parent);
	struct ak881x *ak881x;
	u8 ifmode, data;

	if (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA)) {
		dev_warn(&adapter->dev,
			 "I2C-Adapter doesn't support I2C_FUNC_SMBUS_WORD\n");
		return -EIO;
	}

	ak881x = devm_kzalloc(&client->dev, sizeof(*ak881x), GFP_KERNEL);
	if (!ak881x)
		return -ENOMEM;

	v4l2_i2c_subdev_init(&ak881x->subdev, client, &ak881x_subdev_ops);

	data = reg_read(client, AK881X_DEVICE_ID);

	switch (data) {
	case 0x13:
	case 0x14:
		break;
	default:
		dev_err(&client->dev,
			"No ak881x chip detected, register read %x\n", data);
		return -ENODEV;
	}

	ak881x->revision = reg_read(client, AK881X_DEVICE_REVISION);
	ak881x->pdata = client->dev.platform_data;

	if (ak881x->pdata) {
		if (ak881x->pdata->flags & AK881X_FIELD)
			ifmode = 4;
		else
			ifmode = 0;

		switch (ak881x->pdata->flags & AK881X_IF_MODE_MASK) {
		case AK881X_IF_MODE_BT656:
			ifmode |= 1;
			break;
		case AK881X_IF_MODE_MASTER:
			ifmode |= 2;
			break;
		case AK881X_IF_MODE_SLAVE:
		default:
			break;
		}

		dev_dbg(&client->dev, "IF mode %x\n", ifmode);


		reg_write(client, AK881X_INTERFACE_MODE, ifmode | (20 << 3));
	}


	ak881x->lines = 480;

	dev_info(&client->dev, "Detected an ak881x chip ID %x, revision %x\n",
		 data, ak881x->revision);

	return 0;
}
