btr_cur_update_alloc_zip(

	page_zip_des_t*	page_zip,
	buf_block_t*	block,
	dict_index_t*	index,
	ulint		length,
	ibool		create,

	mtr_t*		mtr)
{
	ut_a(page_zip == buf_block_get_page_zip(block));
	ut_ad(page_zip);
	ut_ad(!dict_index_is_ibuf(index));

	if (page_zip_available(page_zip, dict_index_is_clust(index),
			       length, create)) {
		return(TRUE);
	}

	if (!page_zip->m_nonempty) {


		return(FALSE);
	}

	if (!page_zip_compress(page_zip, buf_block_get_frame(block),
			       index, mtr)) {

		return(FALSE);
	}


	if (!page_zip_available(page_zip, dict_index_is_clust(index),
				length, create)) {

		if (!dict_index_is_clust(index)
		    && page_is_leaf(buf_block_get_frame(block))) {
			ibuf_reset_free_bits(block);
		}
		return(FALSE);
	}

	return(TRUE);
}
