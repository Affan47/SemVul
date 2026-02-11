summary(struct io_data *io_data, __maybe_unused SOCKETTYPE c, __maybe_unused char *param, bool isjson, __maybe_unused char group)
{
	struct api_data *root = NULL;
	char buf[TMPBUFSIZ];
	bool io_open;
	double utility, mhs, work_utility;

	message(io_data, MSG_SUMM, 0, NULL, isjson);
	io_open = io_add(io_data, isjson ? COMSTR JSON_SUMMARY : _SUMMARY COMSTR);


	mutex_lock(&hash_lock);

	utility = total_accepted / ( total_secs ? total_secs : 1 ) * 60;
	mhs = total_mhashes_done / total_secs;
	work_utility = total_diff1 / ( total_secs ? total_secs : 1 ) * 60;

	root = api_add_elapsed(root, "Elapsed", &(total_secs), true);
	root = api_add_mhs(root, "MHS av", &(mhs), false);
	root = api_add_uint(root, "Found Blocks", &(found_blocks), true);
	root = api_add_int(root, "Getworks", &(total_getworks), true);
	root = api_add_int(root, "Accepted", &(total_accepted), true);
	root = api_add_int(root, "Rejected", &(total_rejected), true);
	root = api_add_int(root, "Hardware Errors", &(hw_errors), true);
	root = api_add_utility(root, "Utility", &(utility), false);
	root = api_add_int(root, "Discarded", &(total_discarded), true);
	root = api_add_int(root, "Stale", &(total_stale), true);
	root = api_add_uint(root, "Get Failures", &(total_go), true);
	root = api_add_uint(root, "Local Work", &(local_work), true);
	root = api_add_uint(root, "Remote Failures", &(total_ro), true);
	root = api_add_uint(root, "Network Blocks", &(new_blocks), true);
	root = api_add_mhtotal(root, "Total MH", &(total_mhashes_done), true);
	root = api_add_utility(root, "Work Utility", &(work_utility), false);
	root = api_add_diff(root, "Difficulty Accepted", &(total_diff_accepted), true);
	root = api_add_diff(root, "Difficulty Rejected", &(total_diff_rejected), true);
	root = api_add_diff(root, "Difficulty Stale", &(total_diff_stale), true);
	root = api_add_uint64(root, "Best Share", &(best_diff), true);

	mutex_unlock(&hash_lock);

	root = print_data(root, buf, isjson, false);
	io_add(io_data, buf);
	if (isjson && io_open)
		io_close(io_data);
}
