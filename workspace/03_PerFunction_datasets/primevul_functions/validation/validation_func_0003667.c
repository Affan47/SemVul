static int apply_filters(struct archive_read* a) {
	struct filter_info* flt;
	struct rar5* rar = get_context(a);
	int ret;

	rar->cstate.all_filters_applied = 0;


	if(CDE_OK == cdeque_front(&rar->cstate.filters,
	    cdeque_filter_p(&flt))) {


		if(rar->cstate.write_ptr > flt->block_start &&
		    rar->cstate.write_ptr >= flt->block_start +
		    flt->block_length) {


			if(rar->cstate.last_write_ptr == flt->block_start) {


				ret = run_filter(a, flt);
				if(ret != ARCHIVE_OK) {

					return ret;
				}


				(void) cdeque_pop_front(&rar->cstate.filters,
				    cdeque_filter_p(&flt));

				free(flt);
			} else {


				push_window_data(a, rar,
				    rar->cstate.last_write_ptr,
				    flt->block_start);
			}


			return ARCHIVE_RETRY;
		}
	}

	rar->cstate.all_filters_applied = 1;
	return ARCHIVE_OK;
}
