set_auto_pwm(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t count)
{
	struct it87_data *data = dev_get_drvdata(dev);
	struct sensor_device_attribute_2 *sensor_attr =
			to_sensor_dev_attr_2(attr);
	int nr = sensor_attr->nr;
	int point = sensor_attr->index;
	long val;

	if (kstrtol(buf, 10, &val) < 0 || val < 0 || val > 255)
		return -EINVAL;

	mutex_lock(&data->update_lock);
	data->auto_pwm[nr][point] = pwm_to_reg(data, val);
	it87_write_value(data, IT87_REG_AUTO_PWM(nr, point),
			 data->auto_pwm[nr][point]);
	mutex_unlock(&data->update_lock);
	return count;
}
