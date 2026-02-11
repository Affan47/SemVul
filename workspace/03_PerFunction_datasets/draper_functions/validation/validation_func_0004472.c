run_forced_trials(int bout) {
	int n, msg, side;
	uint64_t forced_side = bit_shuffle(forced_trials);
	time_t time_stamp;
	for (n = 0; time_check() && n < forced_trials; n++) {
		side = ((forced_side>>n) & 0x01);
		flush_events();

		send_msg(RPiMsgSetOn | RPiPin(side+4));

		sleep(2);

		time_stamp = time(NULL);
		send_msg(RPiMsgSetOff | RPiPin(side+4));
		log_data(-1, n, time_stamp - start_time, side);
		play_song(side);
		while (time_check() && now < time_stamp + intertrial_sec) {
			flush_events();
			sleep(1);
		}
	}
	return 0;
}
