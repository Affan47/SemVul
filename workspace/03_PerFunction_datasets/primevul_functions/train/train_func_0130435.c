repeat(p, start, from, to)
register struct parse *p;
sopno start;
int from;
int to;
{
	register sopno finish = HERE();
#	define	N	2
#	define	INF	3
#	define	REP(f, t)	((f)*8 + (t))
#	define	MAP(n)	(((n) <= 1) ? (n) : ((n) == RE_INFINITY) ? INF : N)
	register sopno copy;

	if (p->error != 0)
		return;

	assert(from <= to);

	switch (REP(MAP(from), MAP(to))) {
	case REP(0, 0):
		DROP(finish-start);
		break;
	case REP(0, 1):
	case REP(0, N):
	case REP(0, INF):

		INSERT(OCH_, start);
		repeat(p, start+1, 1, to);
		ASTERN(OOR1, start);
		AHEAD(start);
		EMIT(OOR2, 0);
		AHEAD(THERE());
		ASTERN(O_CH, THERETHERE());
		break;
	case REP(1, 1):

		break;
	case REP(1, N):

		INSERT(OCH_, start);
		ASTERN(OOR1, start);
		AHEAD(start);
		EMIT(OOR2, 0);
		AHEAD(THERE());
		ASTERN(O_CH, THERETHERE());
		copy = dupl(p, start+1, finish+1);
		assert(copy == finish+4);
		repeat(p, copy, 1, to-1);
		break;
	case REP(1, INF):
		INSERT(OPLUS_, start);
		ASTERN(O_PLUS, start);
		break;
	case REP(N, N):
		copy = dupl(p, start, finish);
		repeat(p, copy, from-1, to-1);
		break;
	case REP(N, INF):
		copy = dupl(p, start, finish);
		repeat(p, copy, from-1, to);
		break;
	default:
		SETERROR(REG_ASSERT);
		break;
	}
}
