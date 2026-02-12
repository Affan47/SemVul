static void get_clef(struct SYMBOL *s)
{
	struct SYMBOL *s2;
	struct VOICE_S *p_voice;
	int voice;

	p_voice = curvoice;
	s->type = CLEF;
	if (s->abc_prev->abc_type == ABC_T_INFO) {
		switch (s->abc_prev->text[0]) {
		case 'K':
			if (s->abc_prev->state != ABC_S_HEAD)
				break;
			for (voice = 0; voice < MAXVOICE; voice++) {
				voice_tb[voice].s_clef = s;
				if (s->u.clef.type == PERC)
					voice_tb[voice].perc = 1;
			}
			return;
		case 'V':
			p_voice = &voice_tb[(int) s->abc_prev->u.voice.voice];
			curvoice = p_voice;
			break;
		}
	}

	if (is_tune_sig()) {
		p_voice->s_clef = s;
	} else {

#if 0
		sym_link(s, CLEF);
#else

		s2 = p_voice->last_sym;
		if (s2 && s2->prev
		 && s2->time == curvoice->time
		 && (s2->type == KEYSIG || s2->type == BAR)) {
			struct SYMBOL *s3;

			for (s3 = s2; s3->prev; s3 = s3->prev) {
				switch (s3->prev->type) {
				case KEYSIG:
				case BAR:
					continue;
				}
				break;
			}
			p_voice->last_sym = s3->prev;
			sym_link(s, CLEF);
			s->next = s3;
			s3->prev = s;
			p_voice->last_sym = s2;
		} else {
			sym_link(s, CLEF);
		}
#endif
		s->aux = 1;
	}
	p_voice->perc = s->u.clef.type == PERC;
	if (s->u.clef.type == AUTOCLEF)
		s->sflags |= S_CLEF_AUTO;
}
