getdimen(int *chp, dimen *d, ftnlen delta, ftnlen extent, ftnlen *x1)
#endif
{
	register int k;
	ftnlen x2, x3;

	if (k = getnum(chp, x1))
		return k;
	x3 = 1;
	if (*chp == ':') {
		if (k = getnum(chp, &x2))
			return k;
		x2 -= *x1;
		if (*chp == ':') {
			if (k = getnum(chp, &x3))
				return k;
			if (!x3)
				return 123;
			x2 /= x3;
			colonseen = 1;
			}
		if (x2 < 0 || x2 >= extent)
			return 123;
		d->extent = x2 + 1;
		}
	else
		d->extent = 1;
	d->curval = 0;
	d->delta = delta;
	d->stride = x3;
	return 0;
	}
