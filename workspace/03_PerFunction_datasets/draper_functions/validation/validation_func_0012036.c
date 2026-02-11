fan_set_state_acpi4(struct acpi_device *device, unsigned long state)
{
	struct acpi_fan *fan = acpi_driver_data(device);
	acpi_status status;

	if (state >= fan->fps_count)
		return -EINVAL;

	status = acpi_execute_simple_method(device->handle, "_FSL",
					    fan->fps[state].control);
	if (ACPI_FAILURE(status)) {
		dev_dbg(&device->dev, "Failed to set state by _FSL\n");
		return status;
	}

	return 0;
}
