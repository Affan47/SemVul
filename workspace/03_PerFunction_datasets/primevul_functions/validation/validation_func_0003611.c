static int process_head_service(struct archive_read* a, struct rar5* rar,
    struct archive_entry* entry, size_t block_flags)
{

	int ret = process_head_file(a, rar, entry, block_flags);
	if(ret != ARCHIVE_OK)
		return ret;

	rar->file.service = 1;


	ret = rar5_read_data_skip(a);
	if(ret != ARCHIVE_OK)
		return ret;


	return ARCHIVE_RETRY;
}
