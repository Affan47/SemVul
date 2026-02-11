get_root_bridge_busnr_callback(struct acpi_resource *resource, void *data)
{
	struct resource *res = data;
	struct acpi_resource_address64 address;
	acpi_status status;

	status = acpi_resource_to_address64(resource, &address);
	if (ACPI_FAILURE(status))
		return AE_OK;

	if ((address.address.address_length > 0) &&
	    (address.resource_type == ACPI_BUS_NUMBER_RANGE)) {
		res->start = address.address.minimum;
		res->end = address.address.minimum + address.address.address_length - 1;
	}

	return AE_OK;
}
