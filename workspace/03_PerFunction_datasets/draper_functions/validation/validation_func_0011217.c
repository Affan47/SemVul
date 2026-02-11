store_char(ch, a, rep, pos)
	LWCHAR ch;
	int a;
	char *rep;
	POSITION pos;
{
	int w;
	int replen;
	char cs;

	w = (a & (AT_UNDERLINE|AT_BOLD));
	if (w != AT_NORMAL)
		last_overstrike = w;

#if HILITE_SEARCH
	{
		int matches;
		if (is_hilited(pos, pos+1, 0, &matches))
		{


			if (a != AT_ANSI)
				a |= AT_HILITE;
		}
	}
#endif

	if (ctldisp == OPT_ONPLUS && in_ansi_esc_seq())
	{
		if (!is_ansi_end(ch) && !is_ansi_middle(ch)) {

			char *p = &linebuf[curr];
			LWCHAR bch;
			do {
				bch = step_char(&p, -1, linebuf);
			} while (p > linebuf && !IS_CSI_START(bch));
			curr = p - linebuf;
			return 0;
		}
		a = AT_ANSI;
		w = 0;
	}
	else if (ctldisp == OPT_ONPLUS && IS_CSI_START(ch))
	{
		a = AT_ANSI;
		w = 0;
	}
	else
	{
		char *p = &linebuf[curr];
		LWCHAR prev_ch = step_char(&p, -1, linebuf);
		w = pwidth(ch, a, prev_ch);
	}

	if (ctldisp != OPT_ON && column + w + attr_ewidth(a) > sc_width)


		return (1);

	if (rep == NULL)
	{
		cs = (char) ch;
		rep = &cs;
		replen = 1;
	} else
	{
		replen = utf_len(rep[0]);
	}
	if (curr + replen >= size_linebuf-6)
	{


		if (expand_linebuf())
			return (1);
	}

	while (replen-- > 0)
	{
		linebuf[curr] = *rep++;
		attr[curr] = a;
		curr++;
	}
	column += w;
	return (0);
}
