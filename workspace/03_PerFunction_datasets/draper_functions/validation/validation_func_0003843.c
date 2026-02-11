acpi_ut_delete_internal_object_list(union acpi_operand_object **obj_list)
{
	union acpi_operand_object **internal_obj;

	ACPI_FUNCTION_ENTRY();


	for (internal_obj = obj_list; *internal_obj; internal_obj++) {
		acpi_ut_remove_reference(*internal_obj);
	}


	ACPI_FREE(obj_list);
	return;
}
