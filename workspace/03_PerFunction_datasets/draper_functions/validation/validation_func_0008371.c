d_pf(struct deco_elt *de)
{
	struct SYMBOL *s;
	struct deco_def_s *dd, *dd2;
	float x, x2;
	char *str;
	int up;

	s = de->s;
	dd = &deco_def_tb[de->t];

	up = dyn_p(s, POS_VOL);
	if (up)
		de->flags |= DE_UP;

	x = s->x - dd->wl;
	if (de->prev != 0 && de->prev->s == s
	    && ((de->flags ^ de->prev->flags) & DE_UP) == 0) {
		dd2 = &deco_def_tb[de->prev->t];
		if (dd2->func >= 6) {
			x2 = de->prev->x + de->prev->v + 4;
			if (x2 > x)
				x = x2;
		}
	}

	str = dd->name;
	if (dd->str != 0 && dd->str != 255)
		str = str_tb[dd->str];

	de->v = dd->wl + dd->wr;
	de->x = x;
	de->y = y_get(s, up, s->x, de->v, dd->h);
	de->str = str;

}
