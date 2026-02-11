__erst_read_to_erange(u64 record_id, u64 *offset)
{
	int rc;

	if (erst_erange.attr & ERST_RANGE_NVRAM)
		return __erst_read_to_erange_from_nvram(
			record_id, offset);

	rc = __erst_read_from_storage(record_id, 0);
	if (rc)
		return rc;
	*offset = 0;

	return 0;
}
