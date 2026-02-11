preadbuffer(void)
{
	char *q;
	int more;
#ifndef SMALL
	int something;
#endif
	char savec;

	while (unlikely(parsefile->strpush)) {
		if (
			parsenleft == -1 && parsefile->strpush->ap &&
			parsenextc[-1] != ' ' && parsenextc[-1] != '\t'
		) {
			return PEOA;
		}
		popstring();
		if (--parsenleft >= 0)
			return (signed char)*parsenextc++;
	}
	if (unlikely(parsenleft == EOF_NLEFT || parsefile->buf == NULL))
		return PEOF;
	flushout(&output);
#ifdef FLUSHERR
	flushout(&errout);
#endif

	more = parselleft;
	if (more <= 0) {
again:
		if ((more = preadfd()) <= 0) {
			parselleft = parsenleft = EOF_NLEFT;
			return PEOF;
		}
	}

	q = parsenextc;


#ifndef SMALL
	something = 0;
#endif
	for (;;) {
		int c;

		more--;
		c = *q;

		if (!c)
			memmove(q, q + 1, more);
		else {
			q++;

			if (c == '\n') {
				parsenleft = q - parsenextc - 1;
				break;
			}

#ifndef SMALL
			switch (c) {
			default:
				something = 1;

			case '\t':
			case ' ':
				break;
			}
#endif
		}

		if (more <= 0) {
			parsenleft = q - parsenextc - 1;
			if (parsenleft < 0)
				goto again;
			break;
		}
	}
	parselleft = more;

	savec = *q;
	*q = '\0';

#ifndef SMALL
	if (parsefile->fd == 0 && hist && something) {
		HistEvent he;
		INTOFF;
		history(hist, &he, whichprompt == 1? H_ENTER : H_APPEND,
		    parsenextc);
		INTON;
	}
#endif

	if (vflag) {
		out2str(parsenextc);
#ifdef FLUSHERR
		flushout(out2);
#endif
	}

	*q = savec;

	return (signed char)*parsenextc++;
}
