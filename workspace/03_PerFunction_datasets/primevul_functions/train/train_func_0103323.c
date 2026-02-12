static int __init parse_acpi(char *arg)
{
	if (!arg)
		return -EINVAL;


	if (strcmp(arg, "off") == 0) {
		disable_acpi();
	}

	else if (strcmp(arg, "force") == 0) {
		acpi_force = 1;
		acpi_disabled = 0;
	}

	else if (strcmp(arg, "strict") == 0) {
		acpi_strict = 1;
	}

	else if (strcmp(arg, "rsdt") == 0) {
		acpi_gbl_do_not_use_xsdt = TRUE;
	}

	else if (strcmp(arg, "noirq") == 0) {
		acpi_noirq_set();
	}

	else if (strcmp(arg, "copy_dsdt") == 0) {
		acpi_gbl_copy_dsdt_locally = 1;
	}

	else if (strcmp(arg, "nocmcff") == 0) {
		acpi_disable_cmcff = 1;
	} else {

		return -EINVAL;
	}
	return 0;
}
