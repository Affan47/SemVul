static int process_block(struct archive_read* a) {
	const uint8_t* p;
	struct rar5* rar = get_context(a);
	int ret;


	if(rar->main.volume && rar->file.bytes_remaining == 0) {
		ret = advance_multivolume(a);
		if(ret != ARCHIVE_OK)
			return ret;
	}

	if(rar->cstate.block_parsing_finished) {
		ssize_t block_size;
		ssize_t to_skip;
		ssize_t cur_block_size;


		if(!read_ahead(a, 6, &p)) {

			return ARCHIVE_EOF;
		}


		ret = parse_block_header(a, p, &block_size,
		    &rar->last_block_hdr);
		if(ret != ARCHIVE_OK) {
			return ret;
		}


		to_skip = sizeof(struct compressed_block_header) +
			bf_byte_count(&rar->last_block_hdr) + 1;

		if(ARCHIVE_OK != consume(a, to_skip))
			return ARCHIVE_EOF;

		rar->file.bytes_remaining -= to_skip;


		cur_block_size =
			rar5_min(rar->file.bytes_remaining, block_size);

		if(block_size > rar->file.bytes_remaining) {


			ret = merge_block(a, block_size, &p);
			if(ret != ARCHIVE_OK) {
				return ret;
			}

			cur_block_size = block_size;


		} else {
			rar->cstate.switch_multivolume = 0;


			if(!read_ahead(a, 4 + cur_block_size, &p)) {

				return ARCHIVE_EOF;
			}
		}

		rar->cstate.block_buf = p;
		rar->cstate.cur_block_size = cur_block_size;
		rar->cstate.block_parsing_finished = 0;

		rar->bits.in_addr = 0;
		rar->bits.bit_addr = 0;

		if(bf_is_table_present(&rar->last_block_hdr)) {

			ret = parse_tables(a, rar, p);
			if(ret != ARCHIVE_OK) {


				return ret;
			}
		}
	} else {

		p = rar->cstate.block_buf;
	}


	ret = do_uncompress_block(a, p);
	if(ret != ARCHIVE_OK) {
		return ret;
	}

	if(rar->cstate.block_parsing_finished &&
	    rar->cstate.switch_multivolume == 0 &&
	    rar->cstate.cur_block_size > 0)
	{


		if(ARCHIVE_OK != consume(a, rar->cstate.cur_block_size))
			return ARCHIVE_FATAL;

		rar->file.bytes_remaining -= rar->cstate.cur_block_size;
	} else if(rar->cstate.switch_multivolume) {


		rar->cstate.switch_multivolume = 0;
	}

	return ARCHIVE_OK;
}
