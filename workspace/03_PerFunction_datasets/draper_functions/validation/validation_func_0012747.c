d_cresc(struct deco_elt *de)
{
	struct SYMBOL *s, *s2;
	struct deco_def_s *dd, *dd2;
	struct deco_elt *de1;
	int up;
	float x, dx, x2;

	if (de->flags & DE_LDST)
		return;
	s2 = de->s;
	de1 = de->start;
	if (de1 != 0) {
		s = de1->s;
		x = s->x + 3;
	} else {
		s = first_note;
		x = s->x - s->wl - 4;
	}
	de->staff = s2->staff;
	de->flags &= ~DE_LDEN;
	de->flags |= DE_VAL;
	up = dyn_p(s2, POS_DYN);
	if (up)
		de->flags |= DE_UP;


	if (de1 != 0 && de1->prev != 0 && de1->prev->s == s
	    && ((de->flags ^ de1->prev->flags) & DE_UP) == 0) {
		dd2 = &deco_def_tb[de1->prev->t];
		if (dd2->func >= 6) {
			x2 = de1->prev->x + de1->prev->v + 4;
			if (x2 > x)
				x = x2;
		}
	}

	if (de->defl & DEF_NOEN) {
		dx = de->x - x;
		if (dx < 20) {
			x = de->x - 20 - 3;
			dx = 20;
		}
	} else {
		x2 = s2->x;
		if (de->next != 0 && de->next->s == s
		    && ((de->flags ^ de->next->flags) & DE_UP) == 0) {
			dd2 = &deco_def_tb[de->next->t];
			if (dd2->func >= 6)
				x2 -= 5;
		}
		dx = x2 - x - 4;
		if (dx < 20) {
			x -= (20 - dx) * 0.5;
			if (de->start == 0)
				x -= (20 - dx) * 0.5;
			dx = 20;
		}
	}

	de->v = dx;
	de->x = x;
	dd = &deco_def_tb[de->t];
	de->y = y_get(s2, up, x, dx, dd->h);

}
