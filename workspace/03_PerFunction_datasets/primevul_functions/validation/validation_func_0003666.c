static int merge_block(struct archive_read* a, ssize_t block_size,
    const uint8_t** p)
{
	struct rar5* rar = get_context(a);
	ssize_t cur_block_size, partial_offset = 0;
	const uint8_t* lp;
	int ret;

	if(rar->merge_mode) {
		archive_set_error(&a->archive, ARCHIVE_ERRNO_PROGRAMMER,
		    "Recursive merge is not allowed");

		return ARCHIVE_FATAL;
	}


	rar->cstate.switch_multivolume = 1;


	if(rar->vol.push_buf)
		free((void*) rar->vol.push_buf);


	rar->vol.push_buf = malloc(block_size + 8);
	if(!rar->vol.push_buf) {
		archive_set_error(&a->archive, ENOMEM,
		    "Can't allocate memory for a merge block buffer.");
		return ARCHIVE_FATAL;
	}


	memset(&rar->vol.push_buf[block_size], 0, 8);


	while(1) {


		cur_block_size = rar5_min(rar->file.bytes_remaining,
		    block_size - partial_offset);

		if(cur_block_size == 0) {
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_FILE_FORMAT,
			    "Encountered block size == 0 during block merge");
			return ARCHIVE_FATAL;
		}

		if(!read_ahead(a, cur_block_size, &lp))
			return ARCHIVE_EOF;


		if(partial_offset + cur_block_size > block_size) {
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_PROGRAMMER,
			    "Consumed too much data when merging blocks.");
			return ARCHIVE_FATAL;
		}


		memcpy(&rar->vol.push_buf[partial_offset], lp, cur_block_size);


		if(ARCHIVE_OK != consume(a, cur_block_size))
			return ARCHIVE_EOF;


		partial_offset += cur_block_size;
		rar->file.bytes_remaining -= cur_block_size;


		if(partial_offset == block_size) {
			break;
		}


		if(rar->file.bytes_remaining == 0) {
			rar->merge_mode++;
			ret = advance_multivolume(a);
			rar->merge_mode--;
			if(ret != ARCHIVE_OK) {
				return ret;
			}
		}
	}

	*p = rar->vol.push_buf;


	return ARCHIVE_OK;
}
