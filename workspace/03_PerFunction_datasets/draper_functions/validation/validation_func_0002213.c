ad5398_write_reg(struct i2c_client *client, const unsigned short data)
{
	unsigned short val;
	int ret;

	val = cpu_to_be16(data);
	ret = i2c_master_send(client, (char *)&val, 2);
	if (ret < 0)
		dev_err(&client->dev, "I2C write error\n");

	return ret;
}
