zdivi(ZVALUE z, long n, ZVALUE *res)
{
	HALF *h1, *sd;
	FULL val;
	HALF divval[2];
	ZVALUE div;
	ZVALUE dest;
	LEN len;

	if (n == 0) {
		math_error("Division by zero");

	}
	if (ziszero(z)) {
		*res = _zero_;
		return 0;
	}
	if (n < 0) {
		n = -n;
		z.sign = !z.sign;
	}
	if (n == 1) {
		zcopy(z, res);
		return 0;
	}


	if (n & ~BASE1) {
		div.sign = 0;
		div.v = divval;
		divval[0] = (HALF) n;
#if LONG_BITS > BASEB
		divval[1] = (HALF)(((FULL) n) >> BASEB);
		div.len = 2;
#else
		div.len = 1;
#endif
		zdiv(z, div, res, &dest, 0);
		n = ztolong(dest);
		zfree(dest);
		return n;
	}


	len = z.len;
	dest.sign = z.sign;
	dest.len = len;
	dest.v = alloc(len);
	h1 = z.v + len;
	sd = dest.v + len;
	val = 0;
	while (len--) {
		val = ((val << BASEB) + ((FULL) *--h1));
		*--sd = (HALF)(val / n);
		val %= n;
	}
	zquicktrim(dest);
	*res = dest;
	return (long)val;
}
