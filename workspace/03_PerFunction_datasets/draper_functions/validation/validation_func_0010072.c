snd_es1968_bob_dec(struct es1968 *chip)
{
	chip->bobclient--;
	if (chip->bobclient <= 0)
		snd_es1968_bob_stop(chip);
	else if (chip->bob_freq > ESM_BOB_FREQ) {

		int max_freq = ESM_BOB_FREQ;
		struct esschan *es;
		list_for_each_entry(es, &chip->substream_list, list) {
			if (max_freq < es->bob_freq)
				max_freq = es->bob_freq;
		}
		if (max_freq != chip->bob_freq) {
			snd_es1968_bob_stop(chip);
			chip->bob_freq = max_freq;
			snd_es1968_bob_start(chip);
		}
	}
}
