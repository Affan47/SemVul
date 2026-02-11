cob_intr_exception_file (void)
{
	size_t		flen;
	cob_field_attr	attr;
	cob_field	field;

	COB_ATTR_INIT (COB_TYPE_ALPHANUMERIC, 0, 0, 0, NULL);
	COB_FIELD_INIT (0, NULL, &attr);
	if (cob_exception_code == 0 || !cob_error_file ||
	    (cob_exception_code & 0x0500) != 0x0500) {
		field.size = 2;
		make_field_entry (&field);
		memcpy (curr_field->data, "00", 2);
	} else {
		flen = strlen (cob_error_file->select_name);
		field.size = flen + 2;
		make_field_entry (&field);
		memcpy (curr_field->data, cob_error_file->file_status, 2);
		memcpy (&(curr_field->data[2]), cob_error_file->select_name, flen);
	}
	return curr_field;
}
