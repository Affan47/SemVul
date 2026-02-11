set_temp(struct device *dev, struct device_attribute *devattr,
			const char *buf, size_t count)
{
	struct sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	struct lm77_data *data = dev_get_drvdata(dev);
	struct i2c_client *client = data->client;
	int nr = attr->index;
	long val;
	int err;

	err = kstrtol(buf, 10, &val);
	if (err)
		return err;

	val = clamp_val(val, LM77_TEMP_MIN, LM77_TEMP_MAX);
	mutex_lock(&data->update_lock);
	data->temp[nr] = val;
	lm77_write_value(client, temp_regs[nr], LM77_TEMP_TO_REG(val));
	mutex_unlock(&data->update_lock);
	return count;
}
