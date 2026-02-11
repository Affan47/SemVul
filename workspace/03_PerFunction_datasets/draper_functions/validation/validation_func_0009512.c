ltc_read_byte_data(struct i2c_client *client, int page, int reg)
{
	int ret;

	ret = ltc_wait_ready(client);
	if (ret < 0)
		return ret;

	return pmbus_read_byte_data(client, page, reg);
}
