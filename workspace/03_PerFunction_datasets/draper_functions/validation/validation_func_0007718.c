acer_gsensor_event(void)
{
	acpi_status status;
	struct acpi_buffer output;
	union acpi_object out_obj[5];

	if (!has_cap(ACER_CAP_ACCEL))
		return -1;

	output.length = sizeof(out_obj);
	output.pointer = out_obj;

	status = acpi_evaluate_object(gsensor_handle, "RDVL", NULL, &output);
	if (ACPI_FAILURE(status))
		return -1;

	if (out_obj->package.count != 4)
		return -1;

	input_report_abs(acer_wmi_accel_dev, ABS_X,
		(s16)out_obj->package.elements[0].integer.value);
	input_report_abs(acer_wmi_accel_dev, ABS_Y,
		(s16)out_obj->package.elements[1].integer.value);
	input_report_abs(acer_wmi_accel_dev, ABS_Z,
		(s16)out_obj->package.elements[2].integer.value);
	input_sync(acer_wmi_accel_dev);
	return 0;
}
