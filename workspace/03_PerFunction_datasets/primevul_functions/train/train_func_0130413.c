dofwd(p, pos, value)
register struct parse *p;
register sopno pos;
sop value;
{

	if (p->error != 0)
		return;

	assert(value < 1<<OPSHIFT);
	p->strip[pos] = OP(p->strip[pos]) | value;
}
