freezeset(p, cs)
register struct parse *p;
register cset *cs;
{
	register uch h = cs->hash;
	register size_t i;
	register cset *top = &p->g->sets[p->g->ncsets];
	register cset *cs2;
	register size_t css = (size_t)p->g->csetsize;


	for (cs2 = &p->g->sets[0]; cs2 < top; cs2++)
		if (cs2->hash == h && cs2 != cs) {

			for (i = 0; i < css; i++)
				if (!!CHIN(cs2, i) != !!CHIN(cs, i))
					break;
			if (i == css)
				break;
		}

	if (cs2 < top) {
		freeset(p, cs);
		cs = cs2;
	}

	return((int)(cs - p->g->sets));
}
