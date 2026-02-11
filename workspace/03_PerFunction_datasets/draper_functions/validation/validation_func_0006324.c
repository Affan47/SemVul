sel_col_prefetch_buf_free(

	sel_buf_t*	prefetch_buf)
{
	sel_buf_t*	sel_buf;
	ulint		i;

	for (i = 0; i < SEL_MAX_N_PREFETCH; i++) {
		sel_buf = prefetch_buf + i;

		if (sel_buf->val_buf_size > 0) {

			mem_free(sel_buf->data);
		}
	}

	mem_free(prefetch_buf);
}
