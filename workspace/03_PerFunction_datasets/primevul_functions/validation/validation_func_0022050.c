static int __init parse_acpi(char *arg)
{
	if (!arg)
		return -EINVAL;


	if (strcmp(arg, "off") == 0) {
		disable_acpi();
	}

	else if (strcmp(arg, "force") == 0) {
		acpi_force = 1;
		acpi_ht = 1;
		acpi_disabled = 0;
	}

	else if (strcmp(arg, "strict") == 0) {
		acpi_strict = 1;
	}

	else if (strcmp(arg, "ht") == 0) {
		if (!acpi_force)
			disable_acpi();
		acpi_ht = 1;
	}

	else if (strcmp(arg, "noirq") == 0) {
		acpi_noirq_set();
	} else {

		return -EINVAL;
	}
	return 0;
}
