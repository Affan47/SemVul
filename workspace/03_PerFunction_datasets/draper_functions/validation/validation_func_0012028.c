read_byte(struct i2c_client *client, u8 reg)
{
	int res = i2c_smbus_read_byte_data(client, reg);
	if (res < 0) {
		dev_err(&client->dev,
			"Unable to read from register 0x%02x.\n", reg);
		return 0;
	}
	return res & 0xff;
}
