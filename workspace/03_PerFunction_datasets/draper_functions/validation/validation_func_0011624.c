show_str(struct device *dev,
			struct device_attribute *devattr,
			char *buf)
{
	struct sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	struct acpi_device *acpi_dev = to_acpi_device(dev);
	struct acpi_power_meter_resource *resource = acpi_dev->driver_data;
	acpi_string val;

	switch (attr->index) {
	case 0:
		val = resource->model_number;
		break;
	case 1:
		val = resource->serial_number;
		break;
	case 2:
		val = resource->oem_info;
		break;
	default:
		WARN(1, "Implementation error: unexpected attribute index %d\n",
		     attr->index);
		val = "";
		break;
	}

	return sprintf(buf, "%s\n", val);
}
