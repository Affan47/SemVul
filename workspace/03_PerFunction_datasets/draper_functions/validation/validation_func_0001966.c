__fmtcpy(Fmt *f, const void *vm, int n, int sz)
{
	Rune *rt, *rs, r;
	char *t, *s, *m, *me;
	ulong fl;
	int nc, w;

	m = (char*)vm;
	me = m + sz;
	fl = f->flags;
	w = 0;
	if(fl & FmtWidth)
		w = f->width;
	if((fl & FmtPrec) && n > f->prec)
		n = f->prec;
	if(f->runes){
		if(!(fl & FmtLeft) && __rfmtpad(f, w - n) < 0)
			return -1;
		rt = (Rune*)f->to;
		rs = (Rune*)f->stop;
		for(nc = n; nc > 0; nc--){
			r = *(uchar*)m;
			if(r < Runeself)
				m++;
			else if((me - m) >= UTFmax || fullrune(m, me-m))
				m += chartorune(&r, m);
			else
				break;
			FMTRCHAR(f, rt, rs, r);
		}
		f->nfmt += rt - (Rune *)f->to;
		f->to = rt;
		if(fl & FmtLeft && __rfmtpad(f, w - n) < 0)
			return -1;
	}else{
		if(!(fl & FmtLeft) && __fmtpad(f, w - n) < 0)
			return -1;
		t = (char*)f->to;
		s = (char*)f->stop;
		for(nc = n; nc > 0; nc--){
			r = *(uchar*)m;
			if(r < Runeself)
				m++;
			else if((me - m) >= UTFmax || fullrune(m, me-m))
				m += chartorune(&r, m);
			else
				break;
			FMTRUNE(f, t, s, r);
		}
		f->nfmt += t - (char *)f->to;
		f->to = t;
		if(fl & FmtLeft && __fmtpad(f, w - n) < 0)
			return -1;
	}
	return 0;
}
