static void sort_all(void)
{
	struct SYSTEM *sy;
	struct SYMBOL *s, *prev, *s2;
	struct VOICE_S *p_voice;
	int fl, voice, time, w, wmin, multi, mrest_time;
	int nb, r, set_sy, new_sy;
	struct SYMBOL *vtb[MAXVOICE];
	signed char vn[MAXVOICE];


	mrest_time = -1;
	for (p_voice = first_voice; p_voice; p_voice = p_voice->next)
		vtb[p_voice - voice_tb] = p_voice->sym;


	sy = cursys;
	set_sy = 1;
	new_sy = 0;
	prev = NULL;
	fl = 1;
	multi = -1;
	for (;;) {
		if (set_sy) {
		    fl = 1;

		    if (1) {
			set_sy = 0;
			multi = -1;
			memset(vn, -1, sizeof vn);
			for (p_voice = first_voice;
			     p_voice;
			     p_voice = p_voice->next) {
				voice = p_voice - voice_tb;
				r = sy->voice[voice].range;
				if (r < 0)
					continue;
				vn[r] = voice;
				multi++;
			}
		    }
		}


		wmin = time = (unsigned) ~0 >> 1;

		for (r = 0; r < MAXVOICE; r++) {
			voice = vn[r];
			if (voice < 0)
				break;
			s = vtb[voice];
			if (!s || s->time > time)
				continue;
			w = w_tb[s->type];
			if (s->time < time) {
				time = s->time;
				wmin = w;

			} else if (w < wmin) {
				wmin = w;

			}
#if 0
			if (!(s->sflags & S_SECOND)) {
				nv++;
				if (s->type == BAR)
					nb++;
			}
#endif
			if (s->type == MREST) {
				if (s->u.bar.len == 1)
					mrest_expand(s);
				else if (multi > 0)
					mrest_time = time;
			}
		}
		if (wmin > 127)
			break;

#if 0

		if (nb != 0 && nb != nv) {
			wmin = (unsigned) ~0 >> 1;
			for (r = 0; r < MAXVOICE; r++) {
				voice = vn[r];
				if (voice < 0)
					break;
				s = vtb[voice];
				if (!s || s->time > time
				 || s->type == BAR)
					continue;
				w = w_tb[s->type];
				if (w < wmin)
					wmin = w;
			}
			if (wmin > 127)
				wmin = w_tb[BAR];
		}
#endif


		if (time == mrest_time) {
			nb = 0;
			for (r = 0; r < MAXVOICE; r++) {
				voice = vn[r];
				if (voice < 0)
					break;
				s = vtb[voice];
				if (!s || s->time != time)
					continue;
				w = w_tb[s->type];
				if (w != wmin)
					continue;
				if (s->type != MREST) {
					mrest_time = -1;
					break;
				}
				if (nb == 0) {
					nb = s->u.bar.len;
				} else if (nb != s->u.bar.len) {
					mrest_time = -1;
					break;
				}
			}
			if (mrest_time < 0) {
				for (r = 0; r < MAXVOICE; r++) {
					voice = vn[r];
					if (voice < 0)
						break;
					s = vtb[voice];
					if (s && s->type == MREST)
						mrest_expand(s);
				}
			}
		}


		for (r = 0; r < MAXVOICE; r++) {
			voice = vn[r];
			if (voice < 0)
				break;
			s = vtb[voice];
			if (!s || s->time != time
			 || w_tb[s->type] != wmin)
				continue;
			if (s->type == STAVES) {
				sy = sy->next;
				set_sy = new_sy = 1;
				if (s->prev)
					s->prev->next = s->next;
				else
					voice_tb[voice].sym = s->next;
				if (s->next)
					s->next->prev = s->prev;
			} else {
				if (fl) {
					fl = 0;
					s->sflags |= S_SEQST;
				}
				if (new_sy) {
					new_sy = 0;
					s->sflags |= S_NEW_SY;
				}
				s->ts_prev = prev;
				if (prev) {
					prev->ts_next = s;


				} else {
					tsfirst = s;
				}
				prev = s;
			}
			vtb[voice] = s->next;
		}
		fl = wmin;
	}

	if (!prev)
		return;


	if ((prev->type != BAR && prev->type != FMTCHG)
	 || new_sy) {
		p_voice = &voice_tb[prev->voice];
		p_voice->last_sym = prev;
		s = sym_add(p_voice, FMTCHG);
		s->aux = -1;
		s->time = prev->time + prev->dur;
		s->sflags = S_SEQST;
		if (new_sy)
			s->sflags |= S_NEW_SY;
		prev->ts_next = s;
		s->ts_prev = prev;
		for (;;) {
			prev->sflags &= ~S_EOLN;
			if (prev->sflags & S_SEQST)
				break;
			prev = prev->ts_prev;
		}
	}


	s2 = info['Q' - 'A'];
	if (!s2)
		return;
	info['Q' - 'A'] = NULL;
	s = tsfirst->extra;
	while (s) {
		if (s->type == TEMPO)
			return;
		s = s->next;
	}
	s = tsfirst;
	s2->type = TEMPO;
	s2->voice = s->voice;
	s2->staff = s->staff;
	s2->time = s->time;
	if (s->extra) {
		s2->next = s->extra;
		s2->next->prev = s2;
	}
	s->extra = s2;
}
