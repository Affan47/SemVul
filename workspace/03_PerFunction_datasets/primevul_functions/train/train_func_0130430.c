p_bre(p, end1, end2)
register struct parse *p;
register int end1;
register int end2;
{
	register sopno start = HERE();
	register int first = 1;
	register int wasdollar = 0;

	if (EAT('^')) {
		EMIT(OBOL, 0);
		p->g->iflags |= USEBOL;
		p->g->nbol++;
	}
	while (MORE() && !SEETWO(end1, end2)) {
		wasdollar = p_simp_re(p, first);
		first = 0;
	}
	if (wasdollar) {
		DROP(1);
		EMIT(OEOL, 0);
		p->g->iflags |= USEEOL;
		p->g->neol++;
	}

	if(REQUIRE(HERE() != start, REG_EMPTY)) {}
}
