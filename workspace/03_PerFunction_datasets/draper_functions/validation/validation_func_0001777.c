fmpz_poly_pack_bytes(fmpz_poly_t res, fmpz_poly_t poly, ulong n, ulong bytes)
{
   if (poly->length == 0)
	{
		fmpz_poly_zero(res);
		return;
	}

	long i, j;

	ulong max_bits = FLINT_ABS(fmpz_poly_max_bits(poly));
	ulong limbs = ((n*bytes - 1)>>FLINT_LG_BYTES_PER_LIMB) + 1;
	ulong short_length = (poly->length - 1)/n + 1;


	fmpz_poly_fit_length(res, short_length);
	fmpz_poly_fit_limbs(res, limbs);

	fmpz_poly_t poly_p;

	mp_limb_t * coeff_r = res->coeffs;
   ulong size_p = poly->limbs + 1;
	ulong size_r = res->limbs + 1;


	F_mpn_clear(coeff_r, size_r*short_length);


	for (i = 0, j = 0; i < short_length - 1; i++, j += n, coeff_r += size_r)
	{
      _fmpz_poly_attach_shift(poly_p, poly, j);
		poly_p->length = FLINT_MIN(poly_p->length, n);
		_fmpz_poly_normalise(poly_p);
	   long negate = 1L;
		if (poly_p->length)
			if ((long) poly_p->coeffs[(poly_p->length - 1)*size_p] < 0L) negate = -1L;
		fmpz_poly_byte_pack(coeff_r + 1, poly_p, n, bytes, negate);
		if (negate < 0L) coeff_r[0] = 1 - size_r;
	   else coeff_r[0] = size_r - 1;
	   NORM(coeff_r);
	}

	_fmpz_poly_attach_shift(poly_p, poly, j);
	_fmpz_poly_normalise(poly_p);
	long negate = 1L;
	if (poly_p->length)
	{
		if ((long) poly_p->coeffs[(poly_p->length - 1)*size_p] < 0L) negate = -1L;
      fmpz_poly_byte_pack(coeff_r + 1, poly_p, poly_p->length, bytes, negate);
	}
	if (negate < 0L) coeff_r[0] = 1 - size_r;
	else coeff_r[0] = size_r - 1;
	NORM(coeff_r);

	res->length = short_length;
}
