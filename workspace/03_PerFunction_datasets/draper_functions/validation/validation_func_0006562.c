acpi_add_single_object(struct acpi_device **child,
				  acpi_handle handle, int type,
				  unsigned long long sta)
{
	int result;
	struct acpi_device *device;
	struct acpi_buffer buffer = { ACPI_ALLOCATE_BUFFER, NULL };

	device = kzalloc(sizeof(struct acpi_device), GFP_KERNEL);
	if (!device) {
		printk(KERN_ERR PREFIX "Memory allocation error\n");
		return -ENOMEM;
	}

	acpi_init_device_object(device, handle, type, sta);
	acpi_bus_get_power_flags(device);
	acpi_bus_get_wakeup_device_flags(device);

	result = acpi_device_add(device, acpi_device_release);
	if (result) {
		acpi_device_release(&device->dev);
		return result;
	}

	acpi_power_add_remove_device(device, true);
	acpi_device_add_finalize(device);
	acpi_get_name(handle, ACPI_FULL_PATHNAME, &buffer);
	ACPI_DEBUG_PRINT((ACPI_DB_INFO, "Added %s [%s] parent %s\n",
		dev_name(&device->dev), (char *) buffer.pointer,
		device->parent ? dev_name(&device->parent->dev) : "(null)"));
	kfree(buffer.pointer);
	*child = device;
	return 0;
}
