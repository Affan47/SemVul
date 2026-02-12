doemit(p, op, opnd)
register struct parse *p;
sop op;
size_t opnd;
{

	if (p->error != 0)
		return;


	assert(opnd < 1<<OPSHIFT);


	if (p->slen >= p->ssize)
		enlarge(p, (p->ssize+1) / 2 * 3);
	assert(p->slen < p->ssize);


	p->strip[p->slen++] = SOP(op, opnd);
}
