mpz_poly_max_limbs(mpz_poly_t poly)
{
   if (!poly->length)
      return 0;

   unsigned long temp, limbs = mpz_size(poly->coeffs[0]);

   for (unsigned long i = 1; i < poly->length; i++)
   {
      temp = mpz_size(poly->coeffs[i]);
      if (temp > limbs)
         limbs = temp;
   }

   return limbs;
}
