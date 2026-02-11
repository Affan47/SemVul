rt_timer_callback(void)
{
	if (play_it && !play_it_done) {
		if (!play_moredelay) {
			long delta = delta_time(play_last_time, current_time());

			if (delta < 0) {
				play_writeahead -= (int)((double)delta * 1.2);
			} else if (delta > 15000) {
				play_writeahead -= 2500;
			}
		} else --play_moredelay;

		if (play_writeahead < seq->min_write_ahead_ms)
			play_writeahead = seq->min_write_ahead_ms;

		play_song(play_it, &play_last_time, play_writeahead);
	}
}
