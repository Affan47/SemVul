btr_cur_ins_lock_and_undo(

	ulint		flags,


	btr_cur_t*	cursor,
	dtuple_t*	entry,
	que_thr_t*	thr,
	mtr_t*		mtr,
	ibool*		inherit)


{
	dict_index_t*	index;
	ulint		err;
	rec_t*		rec;
	roll_ptr_t	roll_ptr;


	rec = btr_cur_get_rec(cursor);
	index = cursor->index;

	err = lock_rec_insert_check_and_lock(flags, rec,
					     btr_cur_get_block(cursor),
					     index, thr, mtr, inherit);

	if (err != DB_SUCCESS) {

		return(err);
	}

	if (dict_index_is_clust(index) && !dict_index_is_ibuf(index)) {

		err = trx_undo_report_row_operation(flags, TRX_UNDO_INSERT_OP,
						    thr, index, entry,
						    NULL, 0, NULL,
						    &roll_ptr);
		if (err != DB_SUCCESS) {

			return(err);
		}


		if (!(flags & BTR_KEEP_SYS_FLAG)) {

			row_upd_index_entry_sys_field(entry, index,
						      DATA_ROLL_PTR, roll_ptr);
		}
	}

	return(DB_SUCCESS);
}
