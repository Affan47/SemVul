show_tach(struct device *dev, struct device_attribute *attr,
			 char *buf)
{
	struct adt7475_data *data = adt7475_update_device(dev);
	struct sensor_device_attribute_2 *sattr = to_sensor_dev_attr_2(attr);
	int out;

	if (sattr->nr == ALARM)
		out = (data->alarms >> (sattr->index + 10)) & 1;
	else
		out = tach2rpm(data->tach[sattr->nr][sattr->index]);

	return sprintf(buf, "%d\n", out);
}
