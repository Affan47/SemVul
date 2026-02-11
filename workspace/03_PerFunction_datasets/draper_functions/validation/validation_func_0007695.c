acpi_install_interface(acpi_string interface_name)
{
	acpi_status status;
	struct acpi_interface_info *interface_info;


	if (!interface_name || (strlen(interface_name) == 0)) {
		return (AE_BAD_PARAMETER);
	}

	status = acpi_os_acquire_mutex(acpi_gbl_osi_mutex, ACPI_WAIT_FOREVER);
	if (ACPI_FAILURE(status)) {
		return (status);
	}


	interface_info = acpi_ut_get_interface(interface_name);
	if (interface_info) {


		if (interface_info->flags & ACPI_OSI_INVALID) {
			interface_info->flags &= ~ACPI_OSI_INVALID;
			status = AE_OK;
		} else {
			status = AE_ALREADY_EXISTS;
		}
	} else {


		status = acpi_ut_install_interface(interface_name);
	}

	acpi_os_release_mutex(acpi_gbl_osi_mutex);
	return (status);
}
