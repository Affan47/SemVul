step_time(double offset)
{
	llist_t *item;
	double dtime;
	struct timeval tv;
	char buf[80];
	time_t tval;

	gettimeofday(&tv, NULL);
	dtime = offset + tv.tv_sec;
	dtime += 1.0e-6 * tv.tv_usec;
	d_to_tv(dtime, &tv);

	if (settimeofday(&tv, NULL) == -1)
		bb_perror_msg_and_die("settimeofday");

	tval = tv.tv_sec;
	strftime(buf, sizeof(buf), "%a %b %e %H:%M:%S %Z %Y", localtime(&tval));

	bb_error_msg("setting clock to %s (offset %fs)", buf, offset);


	for (item = G.ntp_peers; item != NULL; item = item->link) {
		peer_t *pp = (peer_t *) item->data;
		reset_peer_stats(pp, offset);


		pp->next_action_time += offset;
	}

	G.cur_time += offset;
	G.last_update_recv_time += offset;
	G.last_script_run += offset;
}
