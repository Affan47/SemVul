thermal_temp_input_show(struct device *dev,
			   struct device_attribute *attr,
			   char *buf)
{
	struct sensor_device_attribute *sensor_attr =
					to_sensor_dev_attr(attr);
	int idx = sensor_attr->index;
	s32 value;
	int res;

	res = thermal_get_sensor(idx, &value);
	if (res)
		return res;
	if (value == TPACPI_THERMAL_SENSOR_NA)
		return -ENXIO;

	return snprintf(buf, PAGE_SIZE, "%d\n", value);
}
