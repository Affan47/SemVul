static int skip_base_block(struct archive_read* a) {
	int ret;
	struct rar5* rar = get_context(a);


	struct archive_entry* entry = archive_entry_new();
	ret = process_base_block(a, entry);


	archive_entry_free(entry);
	if(ret == ARCHIVE_FATAL)
		return ret;

	if(rar->generic.last_header_id == 2 && rar->generic.split_before > 0)
		return ARCHIVE_OK;

	if(ret == ARCHIVE_OK)
		return ARCHIVE_RETRY;
	else
		return ret;
}
