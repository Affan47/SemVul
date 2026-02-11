F_mpz_poly_max_limbs(const F_mpz_poly_t poly)
{
	if (poly->length == 0) return 0;

	ulong max = 1;
   ulong limbs;
	ulong c;


	for (ulong i = 0; i < poly->length; i++)
	{
		c = poly->coeffs[i];
      if (COEFF_IS_MPZ(c))
		{
			limbs = mpz_size(F_mpz_ptr_mpz(c));
			if (limbs > max) max = limbs;
		}
	}

	return max;
}
