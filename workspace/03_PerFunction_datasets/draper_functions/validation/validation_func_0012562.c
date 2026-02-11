F_mpz_poly_scalar_mul(F_mpz_poly_t poly1, const F_mpz_poly_t poly2, const F_mpz_t x)
{

	if ((*x == 0) || (poly2->length == 0))
	{
	   F_mpz_poly_zero(poly1);
		return;
	}


	if (*x == 1L)
	{
	   F_mpz_poly_set(poly1, poly2);
		return;
	}


	if (*x == -1L)
	{
	   F_mpz_poly_neg(poly1, poly2);
		return;
	}

	F_mpz_poly_fit_length(poly1, poly2->length);

	for (ulong i = 0; i < poly2->length; i++)
		F_mpz_mul2(poly1->coeffs + i, poly2->coeffs + i, x);

	_F_mpz_poly_set_length(poly1, poly2->length);
}
