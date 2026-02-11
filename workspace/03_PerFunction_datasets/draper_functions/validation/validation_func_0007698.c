do_ipack_entry(const char *filename,
			  void *symval, char *alias)
{
	DEF_FIELD(symval, ipack_device_id, format);
	DEF_FIELD(symval, ipack_device_id, vendor);
	DEF_FIELD(symval, ipack_device_id, device);
	strcpy(alias, "ipack:");
	ADD(alias, "f", format != IPACK_ANY_FORMAT, format);
	ADD(alias, "v", vendor != IPACK_ANY_ID, vendor);
	ADD(alias, "d", device != IPACK_ANY_ID, device);
	add_wildcard(alias);
	return 1;
}
