sx8654_open(struct input_dev *dev)
{
	struct sx8654 *sx8654 = input_get_drvdata(dev);
	struct i2c_client *client = sx8654->client;
	int error;


	error = i2c_smbus_write_byte_data(client, I2C_REG_TOUCH0,
					  RATE_5000CPS | POWDLY_1_1MS);
	if (error) {
		dev_err(&client->dev, "writing to I2C_REG_TOUCH0 failed");
		return error;
	}

	error = i2c_smbus_write_byte(client, CMD_PENTRG);
	if (error) {
		dev_err(&client->dev, "writing command CMD_PENTRG failed");
		return error;
	}

	enable_irq(client->irq);

	return 0;
}
