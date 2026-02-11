tg_with_in_bps_limit(struct throtl_grp *tg, struct bio *bio,
				 unsigned long *wait)
{
	bool rw = bio_data_dir(bio);
	u64 bytes_allowed, extra_bytes, tmp;
	unsigned long jiffy_elapsed, jiffy_wait, jiffy_elapsed_rnd;

	jiffy_elapsed = jiffy_elapsed_rnd = jiffies - tg->slice_start[rw];


	if (!jiffy_elapsed)
		jiffy_elapsed_rnd = throtl_slice;

	jiffy_elapsed_rnd = roundup(jiffy_elapsed_rnd, throtl_slice);

	tmp = tg->bps[rw] * jiffy_elapsed_rnd;
	do_div(tmp, HZ);
	bytes_allowed = tmp;

	if (tg->bytes_disp[rw] + bio->bi_iter.bi_size <= bytes_allowed) {
		if (wait)
			*wait = 0;
		return true;
	}


	extra_bytes = tg->bytes_disp[rw] + bio->bi_iter.bi_size - bytes_allowed;
	jiffy_wait = div64_u64(extra_bytes * HZ, tg->bps[rw]);

	if (!jiffy_wait)
		jiffy_wait = 1;


	jiffy_wait = jiffy_wait + (jiffy_elapsed_rnd - jiffy_elapsed);
	if (wait)
		*wait = jiffy_wait;
	return 0;
}
