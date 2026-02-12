seterr(p, e)
register struct parse *p;
int e;
{
	if (p->error == 0)
		p->error = e;
	p->next = nuls;
	p->end = nuls;
	return(0);
}
