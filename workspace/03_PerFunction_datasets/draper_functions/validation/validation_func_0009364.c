pdelrect(P *org, long int height, long int right)
{
	P *p = pdup(org);
	P *q = pdup(p);

	while (height--) {
		pcol(p, org->xcol);
		pset(q, p);
		pcol(q, right);
		bdel(p, q);
		pnextl(p);
	}
	prm(p);
	prm(q);
}
