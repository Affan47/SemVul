store_in_max(struct device *dev, struct device_attribute
	*devattr, const char *buf, size_t count)
{
	struct f71882fg_data *data = dev_get_drvdata(dev);
	int err;
	long val;

	err = kstrtol(buf, 10, &val);
	if (err)
		return err;

	val /= 8;
	val = clamp_val(val, 0, 255);

	mutex_lock(&data->update_lock);
	if (data->type == f81866a)
		f71882fg_write8(data, F81866_REG_IN1_HIGH, val);
	else
		f71882fg_write8(data, F71882FG_REG_IN1_HIGH, val);
	data->in1_max = val;
	mutex_unlock(&data->update_lock);

	return count;
}
