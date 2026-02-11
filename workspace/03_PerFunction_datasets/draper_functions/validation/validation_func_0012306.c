elan_i2c_initialize(struct i2c_client *client)
{
	struct device *dev = &client->dev;
	int error;
	u8 val[256];

	error = elan_i2c_write_cmd(client, ETP_I2C_STAND_CMD, ETP_I2C_RESET);
	if (error) {
		dev_err(dev, "device reset failed: %d\n", error);
		return error;
	}


	msleep(100);


	error = i2c_master_recv(client, val, ETP_I2C_INF_LENGTH);
	if (error < 0) {
		dev_err(dev, "failed to read reset response: %d\n", error);
		return error;
	}

	error = elan_i2c_read_block(client, ETP_I2C_DESC_CMD,
				    val, ETP_I2C_DESC_LENGTH);
	if (error) {
		dev_err(dev, "cannot get device descriptor: %d\n", error);
		return error;
	}

	error = elan_i2c_read_block(client, ETP_I2C_REPORT_DESC_CMD,
				    val, ETP_I2C_REPORT_DESC_LENGTH);
	if (error) {
		dev_err(dev, "fetching report descriptor failed.: %d\n", error);
		return error;
	}

	return 0;
}
