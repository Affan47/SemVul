findmust(p, g)
struct parse *p;
register struct re_guts *g;
{
	register sop *scan;
	sop *UNINIT_VAR(start);
	register sop *UNINIT_VAR(newstart);
	register sopno newlen;
	register sop s;
	register char *cp;
	register sopno i;


	if (p->error != 0)
		return;


	newlen = 0;
	scan = g->strip + 1;
	do {
		s = *scan++;
		switch (OP(s)) {
		case OCHAR:
			if (newlen == 0)
				newstart = scan - 1;
			newlen++;
			break;
		case OPLUS_:
		case OLPAREN:
		case ORPAREN:
			break;
		case OQUEST_:
		case OCH_:
			scan--;
			do {
				scan += OPND(s);
				s = *scan;

				if (OP(s) != O_QUEST && OP(s) != O_CH &&
							OP(s) != OOR2) {
					g->iflags |= BAD;
					return;
				}
			} while (OP(s) != O_QUEST && OP(s) != O_CH);

		default:
			if (newlen > g->mlen) {
				start = newstart;
				g->mlen = newlen;
			}
			newlen = 0;
			break;
		}
	} while (OP(s) != OEND);

	if (g->mlen == 0)
		return;


	g->must = malloc((size_t)g->mlen + 1);
	if (g->must == NULL) {
		g->mlen = 0;
		return;
	}
	cp = g->must;
	scan = start;
	for (i = g->mlen; i > 0; i--) {
		while (OP(s = *scan++) != OCHAR)
			continue;
		assert(cp < g->must + g->mlen);
		*cp++ = (char)OPND(s);
	}
	assert(cp == g->must + g->mlen);
	*cp++ = '\0';
}
