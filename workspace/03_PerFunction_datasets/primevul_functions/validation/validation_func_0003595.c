static int do_uncompress_file(struct archive_read* a) {
	struct rar5* rar = get_context(a);
	int ret;
	int64_t max_end_pos;

	if(!rar->cstate.initialized) {


		if(!rar->main.solid || !rar->cstate.window_buf) {
			init_unpack(rar);
		}

		rar->cstate.initialized = 1;
	}

	if(rar->cstate.all_filters_applied == 1) {


		while(1) {
			ret = process_block(a);
			if(ret == ARCHIVE_EOF || ret == ARCHIVE_FATAL)
				return ret;

			if(rar->cstate.last_write_ptr ==
			    rar->cstate.write_ptr) {


				continue;
			}


			break;
		}
	}


	ret = apply_filters(a);
	if(ret == ARCHIVE_RETRY) {
		return ARCHIVE_OK;
	} else if(ret == ARCHIVE_FATAL) {
		return ARCHIVE_FATAL;
	}


	if(cdeque_size(&rar->cstate.filters) > 0) {


		struct filter_info* flt;


		if(CDE_OK != cdeque_front(&rar->cstate.filters,
		    cdeque_filter_p(&flt)))
		{
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_PROGRAMMER,
			    "Can't read first filter");
			return ARCHIVE_FATAL;
		}

		max_end_pos = rar5_min(flt->block_start,
		    rar->cstate.write_ptr);
	} else {


		max_end_pos = rar->cstate.write_ptr;
	}

	if(max_end_pos == rar->cstate.last_write_ptr) {


		return ARCHIVE_RETRY;
	} else {


		push_window_data(a, rar, rar->cstate.last_write_ptr,
		    max_end_pos);
		rar->cstate.last_write_ptr = max_end_pos;
	}

	return ARCHIVE_OK;
}
