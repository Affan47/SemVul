sub_big(bignum_t *x, bignum_t *y, bignum_t *z)
{
	int xl, yl, zl, b, i;
	uint64 *xp, *yp, *zp;

	safety_assert(x->l < BIGSIZE);
	safety_assert(x->l >= 0);
	safety_assert(y->l < BIGSIZE);
	safety_assert(y->l >= 0);

	xl = x->l;
	yl = y->l;
	if (yl > xl)
		return 1;
	xp = &x->d[0];
	yp = &y->d[0];
	zp = &z->d[0];

	for (i = yl, b = 0; i >= 0; i--)
		SUB(*xp++, *yp++, *zp++, b);
	for (i = xl-yl; b && i > 0; i--) {
		uint64 x_sub;
		x_sub = *xp++;
		*zp++ = x_sub - 1;
		b = (x_sub == 0);
	}
	safety_assert(zp - &z->d[0] < BIGSIZE);
	for (; i > 0; i--)
		*zp++ = *xp++;
	safety_assert(zp - &z->d[0] < BIGSIZE);
	if (b)
		return 1;
	zl = xl;
	while (zl > 0 && *--zp == 0)
		zl--;
	z->l = zl;
	safety_assert(z->l < BIGSIZE);
	safety_assert_log(z->l >= 0, "z->l = %d", z->l);
	return 0;
}
