static int is_valid_filter_block_start(struct rar5* rar,
    uint32_t start)
{
	const int64_t block_start = (ssize_t) start + rar->cstate.write_ptr;
	const int64_t last_bs = rar->cstate.last_block_start;
	const ssize_t last_bl = rar->cstate.last_block_length;

	if(last_bs == 0 || last_bl == 0) {

		return 1;
	}

	if(block_start >= last_bs + last_bl) {


		return 1;
	}


	return 0;
}
