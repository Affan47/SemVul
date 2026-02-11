acpi_ex_do_logical_numeric_op(u16 opcode,
			      u64 integer0, u64 integer1, u8 *logical_result)
{
	acpi_status status = AE_OK;
	u8 local_result = FALSE;

	ACPI_FUNCTION_TRACE(ex_do_logical_numeric_op);

	switch (opcode) {
	case AML_LAND_OP:

		if (integer0 && integer1) {
			local_result = TRUE;
		}
		break;

	case AML_LOR_OP:

		if (integer0 || integer1) {
			local_result = TRUE;
		}
		break;

	default:

		status = AE_AML_INTERNAL;
		break;
	}


	*logical_result = local_result;
	return_ACPI_STATUS(status);
}
