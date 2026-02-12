static int skip_unprocessed_bytes(struct archive_read* a) {
	struct rar5* rar = get_context(a);
	int ret;

	if(rar->file.bytes_remaining) {


		if(rar->merge_mode) {


			ret = consume(a, rar->file.bytes_remaining);
			if(ret != ARCHIVE_OK) {
				return ret;
			}
			rar->file.bytes_remaining = 0;
		} else {


			ret = rar5_read_data_skip(a);
			if(ret != ARCHIVE_OK) {
				return ret;
			}
		}
	}

	return ARCHIVE_OK;
}
