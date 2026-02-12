static int push_data_ready(struct archive_read* a, struct rar5* rar,
    const uint8_t* buf, size_t size, int64_t offset)
{
	int i;


	if(rar->skip_mode)
		return ARCHIVE_OK;


	if(offset != rar->file.last_offset + rar->file.last_size) {
		archive_set_error(&a->archive, ARCHIVE_ERRNO_PROGRAMMER,
		    "Sanity check error: output stream is not continuous");
		return ARCHIVE_FATAL;
	}

	for(i = 0; i < rar5_countof(rar->cstate.dready); i++) {
		struct data_ready* d = &rar->cstate.dready[i];
		if(!d->used) {
			d->used = 1;
			d->buf = buf;
			d->size = size;
			d->offset = offset;


			rar->file.last_offset = offset;
			rar->file.last_size = size;


			update_crc(rar, d->buf, d->size);

			return ARCHIVE_OK;
		}
	}


	archive_set_error(&a->archive, ARCHIVE_ERRNO_PROGRAMMER,
	    "Error: premature end of data_ready stack");
	return ARCHIVE_FATAL;
}
