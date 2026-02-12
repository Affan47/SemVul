static void ps_def(struct SYMBOL *s,
			char *p,
			char use)
{
	if (!svg && epsf <= 1) {
		if (secure

		 || use == 's')
			return;
	} else {
		if (use == 'p'
		 || (use == 'g'
		  && file_initialized > 0))
			return;
	}
	if (s->abc_prev)
		s->state = s->abc_prev->state;
	if (s->state == ABC_S_TUNE) {
		if (use == 'g')
			return;
		sym_link(s, FMTCHG);
		s->aux = PSSEQ;
		s->text = p;

		return;
	}
	if (use == 'g') {
		svg_ps(p);
		if (!svg && epsf <= 1)
			return;
	}
	if (file_initialized > 0 || mbf != outbuf)
		a2b("%s\n", p);
	else
		user_ps_add(p, use);
}
