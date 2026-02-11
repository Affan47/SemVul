asus_register_rfkill_notifier(struct asus_wmi *asus, char *node)
{
	acpi_status status;
	acpi_handle handle;

	status = acpi_get_handle(NULL, node, &handle);

	if (ACPI_SUCCESS(status)) {
		status = acpi_install_notify_handler(handle,
						     ACPI_SYSTEM_NOTIFY,
						     asus_rfkill_notify, asus);
		if (ACPI_FAILURE(status))
			pr_warn("Failed to register notify on %s\n", node);
	} else
		return -ENODEV;

	return 0;
}
