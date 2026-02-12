static void push_data(struct archive_read* a, struct rar5* rar,
    const uint8_t* buf, int64_t idx_begin, int64_t idx_end)
{
	const uint64_t wmask = rar->cstate.window_mask;
	const ssize_t solid_write_ptr = (rar->cstate.solid_offset +
	    rar->cstate.last_write_ptr) & wmask;

	idx_begin += rar->cstate.solid_offset;
	idx_end += rar->cstate.solid_offset;


	if((idx_begin & wmask) > (idx_end & wmask)) {


		const ssize_t frag1_size = rar->cstate.window_size -
		    (idx_begin & wmask);
		const ssize_t frag2_size = idx_end & wmask;


		push_data_ready(a, rar, buf + solid_write_ptr, frag1_size,
		    rar->cstate.last_write_ptr);


		push_data_ready(a, rar, buf, frag2_size,
		    rar->cstate.last_write_ptr + frag1_size);

		rar->cstate.last_write_ptr += frag1_size + frag2_size;
	} else {


		push_data_ready(a, rar,
		    buf + solid_write_ptr, (idx_end - idx_begin) & wmask,
		    rar->cstate.last_write_ptr);

		rar->cstate.last_write_ptr += idx_end - idx_begin;
	}
}
