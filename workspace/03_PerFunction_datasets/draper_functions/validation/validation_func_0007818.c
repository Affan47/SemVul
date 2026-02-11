store_pwm_setting(struct device *dev, struct device_attribute
	*devattr, const char *buf, size_t count)
{
	struct sensor_device_attribute_2 *attr = to_sensor_dev_attr_2(devattr);
	struct abituguru_data *data = dev_get_drvdata(dev);
	u8 min;
	unsigned long val;
	ssize_t ret;

	ret = kstrtoul(buf, 10, &val);
	if (ret)
		return ret;

	ret = count;
	val = (val + abituguru_pwm_settings_multiplier[attr->nr] / 2) /
				abituguru_pwm_settings_multiplier[attr->nr];


	if ((attr->index == 0) && ((attr->nr == 1) || (attr->nr == 2)))
		min = 77;
	else
		min = abituguru_pwm_min[attr->nr];


	if (val < min || val > abituguru_pwm_max[attr->nr])
		return -EINVAL;

	mutex_lock(&data->update_lock);

	if ((attr->nr & 1) &&
			(val >= data->pwm_settings[attr->index][attr->nr + 1]))
		ret = -EINVAL;
	else if (!(attr->nr & 1) &&
			(val <= data->pwm_settings[attr->index][attr->nr - 1]))
		ret = -EINVAL;
	else if (data->pwm_settings[attr->index][attr->nr] != val) {
		u8 orig_val = data->pwm_settings[attr->index][attr->nr];
		data->pwm_settings[attr->index][attr->nr] = val;
		if (abituguru_write(data, ABIT_UGURU_FAN_PWM + 1,
				attr->index, data->pwm_settings[attr->index],
				5) <= attr->nr) {
			data->pwm_settings[attr->index][attr->nr] =
				orig_val;
			ret = -EIO;
		}
	}
	mutex_unlock(&data->update_lock);
	return ret;
}
