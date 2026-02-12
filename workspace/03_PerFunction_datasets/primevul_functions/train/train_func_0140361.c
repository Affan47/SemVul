static void get_meter(struct SYMBOL *s)
{
	struct VOICE_S *p_voice;
	int i;

	switch (s->state) {
	case ABC_S_GLOBAL:

		break;
	case ABC_S_HEAD:
		for (i = MAXVOICE, p_voice = voice_tb;
		     --i >= 0;
		     p_voice++) {
			memcpy(&p_voice->meter, &s->u.meter,
			       sizeof p_voice->meter);
			p_voice->wmeasure = s->u.meter.wmeasure;
		}
		break;
	case ABC_S_TUNE:
		curvoice->wmeasure = s->u.meter.wmeasure;
		if (is_tune_sig()) {
			memcpy(&curvoice->meter, &s->u.meter,
				       sizeof curvoice->meter);
			reset_gen();
			break;
		}
		if (s->u.meter.nmeter == 0)
			break;
		sym_link(s, TIMESIG);
		break;
	}
}
