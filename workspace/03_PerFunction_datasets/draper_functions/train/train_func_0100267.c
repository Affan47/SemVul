price (GDate *settlement, GDate *maturity, gnm_float rate, gnm_float yield,
       gnm_float redemption, GoCouponConvention const *conv)
{
	gnm_float a, d, e, sum, den, basem1, exponent, first_term, last_term;
	int       n;

	a = go_coupdaybs (settlement, maturity, conv);
	d = go_coupdaysnc (settlement, maturity, conv);
	e = go_coupdays (settlement, maturity, conv);
	n = coupnum (settlement, maturity, conv);

	den = 100.0 * rate / conv->freq;
	basem1 = yield / conv->freq;
	exponent = d / e;

	if (n == 1)
		return (redemption + den) / (1 + exponent * basem1) -
			a / e * den;

	sum = den * pow1p (basem1, 1 - n - exponent) *
		pow1pm1 (basem1, n) / basem1;

	first_term = redemption / pow1p (basem1, (n - 1.0 + d / e));
	last_term = a / e * den;

	return (first_term + sum - last_term);
}
