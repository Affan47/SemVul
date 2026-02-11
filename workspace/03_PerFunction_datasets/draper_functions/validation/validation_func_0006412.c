fcmplt_ins(BW *bw, unsigned char *line)
{
	P *p;
	int c;

	if (!piseol(bw->cursor)) {
		c = brch(bw->cursor);
		if (joe_isalnum_(bw->b->o.charmap,c))
			return;
	}


	p = pdup(bw->cursor);
	do
		c = prgetc(p);
		while (joe_isalnum_(bw->b->o.charmap,c));
	if (c!=NO_MORE_DATA)
		pgetc(p);

	if (bw->cursor->byte!=p->byte && bw->cursor->byte-p->byte<64) {

		bdel(p,bw->cursor);
		binsm(bw->cursor,sv(line));
		pfwrd(bw->cursor,sLEN(line));
		bw->cursor->xcol = piscol(bw->cursor);
		prm(p);
	} else {
		prm(p);
	}
}
