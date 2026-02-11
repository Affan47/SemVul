mlog_write_initial_log_record(

	const byte*	ptr,


	byte		type,
	mtr_t*		mtr)
{
	byte*	log_ptr;

	ut_ad(type <= MLOG_BIGGEST_TYPE);
	ut_ad(type > MLOG_8BYTES);

	log_ptr = mlog_open(mtr, 11);


	if (log_ptr == NULL) {

		return;
	}

	log_ptr = mlog_write_initial_log_record_fast(ptr, type, log_ptr, mtr);

	mlog_close(mtr, log_ptr);
}
