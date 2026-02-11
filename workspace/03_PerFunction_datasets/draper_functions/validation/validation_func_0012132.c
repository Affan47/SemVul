mpz_poly_mul_classical(mpz_poly_t res, mpz_poly_t poly1, mpz_poly_t poly2)
{
   if (!poly1->length || !poly2->length)
   {

      res->length = 0;
      return;
   }

   if (poly1 == poly2)
   {

      mpz_poly_sqr_classical(res, poly1);
      return;
   }

   unsigned long limbs = mpz_poly_product_max_limbs(poly1, poly2);
   unsigned long length = poly1->length + poly2->length - 1;

   if (res == poly1 || res == poly2)
   {

      mpz_poly_t temp;
      mpz_poly_init3(temp, length, FLINT_BITS * limbs);
      _mpz_poly_mul_classical(temp, poly1, poly2);
      mpz_poly_swap(temp, res);
      mpz_poly_clear(temp);
   }
   else
   {

      mpz_poly_ensure_alloc(res, length);
      _mpz_poly_mul_classical(res, poly1, poly2);
   }
}
