ast_tonepair_start(struct ast_channel *chan, int freq1, int freq2, int duration, int vol)
{
	struct tonepair_def d = { 0, };

	d.freq1 = freq1;
	d.freq2 = freq2;
	d.duration = duration;
	d.vol = (vol < 1) ? 8192 : vol;
	if (ast_activate_generator(chan, &tonepair, &d))
		return -1;
	return 0;
}
