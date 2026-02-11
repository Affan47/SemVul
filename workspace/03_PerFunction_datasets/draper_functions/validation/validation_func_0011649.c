adt7411_detect(struct i2c_client *client,
			  struct i2c_board_info *info)
{
	int val;

	if (!i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		return -ENODEV;

	val = i2c_smbus_read_byte_data(client, ADT7411_REG_MANUFACTURER_ID);
	if (val < 0 || val != ADT7411_MANUFACTURER_ID) {
		dev_dbg(&client->dev,
			"Wrong manufacturer ID. Got %d, expected %d\n",
			val, ADT7411_MANUFACTURER_ID);
		return -ENODEV;
	}

	val = i2c_smbus_read_byte_data(client, ADT7411_REG_DEVICE_ID);
	if (val < 0 || val != ADT7411_DEVICE_ID) {
		dev_dbg(&client->dev,
			"Wrong device ID. Got %d, expected %d\n",
			val, ADT7411_DEVICE_ID);
		return -ENODEV;
	}

	strlcpy(info->type, "adt7411", I2C_NAME_SIZE);

	return 0;
}
