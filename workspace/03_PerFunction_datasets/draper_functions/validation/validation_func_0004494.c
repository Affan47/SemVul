page_rec_validate(

	const rec_t*	rec,
	const ulint*	offsets)
{
	ulint		n_owned;
	ulint		heap_no;
	const page_t*	page;

	page = page_align(rec);
	ut_a(!page_is_comp(page) == !rec_offs_comp(offsets));

	page_rec_check(rec);
	rec_validate(rec, offsets);

	if (page_rec_is_comp(rec)) {
		n_owned = rec_get_n_owned_new(rec);
		heap_no = rec_get_heap_no_new(rec);
	} else {
		n_owned = rec_get_n_owned_old(rec);
		heap_no = rec_get_heap_no_old(rec);
	}

	if (UNIV_UNLIKELY(!(n_owned <= PAGE_DIR_SLOT_MAX_N_OWNED))) {
		fprintf(stderr,
			"InnoDB: Dir slot of rec %lu, n owned too big %lu\n",
			(ulong) page_offset(rec), (ulong) n_owned);
		return(FALSE);
	}

	if (UNIV_UNLIKELY(!(heap_no < page_dir_get_n_heap(page)))) {
		fprintf(stderr,
			"InnoDB: Heap no of rec %lu too big %lu %lu\n",
			(ulong) page_offset(rec), (ulong) heap_no,
			(ulong) page_dir_get_n_heap(page));
		return(FALSE);
	}

	return(TRUE);
}
