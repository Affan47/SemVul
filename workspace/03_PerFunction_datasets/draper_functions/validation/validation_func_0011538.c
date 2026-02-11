set_enable(struct device *dev, struct device_attribute *devattr,
			  const char *buf, size_t count)
{
	struct max6650_data *data = dev_get_drvdata(dev);
	struct i2c_client *client = data->client;
	int max6650_modes[3] = {0, 3, 2};
	unsigned long mode;
	int err;

	err = kstrtoul(buf, 10, &mode);
	if (err)
		return err;

	if (mode > 2)
		return -EINVAL;

	mutex_lock(&data->update_lock);

	data->config = i2c_smbus_read_byte_data(client, MAX6650_REG_CONFIG);
	data->config = (data->config & ~MAX6650_CFG_MODE_MASK)
		       | (max6650_modes[mode] << 4);

	i2c_smbus_write_byte_data(client, MAX6650_REG_CONFIG, data->config);

	mutex_unlock(&data->update_lock);

	return count;
}
