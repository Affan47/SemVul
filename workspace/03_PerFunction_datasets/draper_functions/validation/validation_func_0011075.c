show_pwm_temp_map(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	struct sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	int nr = sensor_attr->index;

	struct it87_data *data = it87_update_device(dev);
	int map;

	if (data->pwm_temp_map[nr] < 3)
		map = 1 << data->pwm_temp_map[nr];
	else
		map = 0;
	return sprintf(buf, "%d\n", map);
}
