show_temp11(struct device *dev, struct device_attribute *devattr,
			   char *buf)
{
	struct sensor_device_attribute_2 *attr = to_sensor_dev_attr_2(devattr);
	struct lm90_data *data = lm90_update_device(dev);
	int temp;

	if (data->kind == adt7461 || data->kind == tmp451)
		temp = temp_from_u16_adt7461(data, data->temp11[attr->index]);
	else if (data->kind == max6646)
		temp = temp_from_u16(data->temp11[attr->index]);
	else
		temp = temp_from_s16(data->temp11[attr->index]);


	if (data->kind == lm99 &&  attr->index <= 2)
		temp += 16000;

	return sprintf(buf, "%d\n", temp);
}
