acpi_bus_scan(acpi_handle handle)
{
	void *device = NULL;

	if (ACPI_SUCCESS(acpi_bus_check_add(handle, 0, NULL, &device)))
		acpi_walk_namespace(ACPI_TYPE_ANY, handle, ACPI_UINT32_MAX,
				    acpi_bus_check_add, NULL, NULL, &device);

	if (device) {
		acpi_bus_attach(device);
		return 0;
	}
	return -ENODEV;
}
