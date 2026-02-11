mpz_poly_sub(mpz_poly_t res, mpz_poly_t poly1, mpz_poly_t poly2)
{
   if (poly1 == poly2)
   {

      res->length = 0;
      return;
   }


   int swapped = 0;
   if (poly1->length > poly2->length)
   {
      swapped = 1;
      SWAP_MPZ_POLY_PTRS(poly1, poly2);
   }

   mpz_poly_ensure_alloc(res, poly2->length);

   unsigned long i;

   if (swapped)
   {
      for (i = 0; i < poly1->length; i++)
         mpz_sub(res->coeffs[i], poly2->coeffs[i], poly1->coeffs[i]);
      for (; i < poly2->length; i++)
         mpz_set(res->coeffs[i], poly2->coeffs[i]);
   }
   else
   {
      for (i = 0; i < poly1->length; i++)
         mpz_sub(res->coeffs[i], poly1->coeffs[i], poly2->coeffs[i]);
      for (; i < poly2->length; i++)
         mpz_neg(res->coeffs[i], poly2->coeffs[i]);
   }

   res->length = poly2->length;
   mpz_poly_normalise(res);
}
