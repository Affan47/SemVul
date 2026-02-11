_fmpz_poly_equal(const fmpz_poly_t input1, const fmpz_poly_t input2)
{
   if (input1 == input2) return 1;
   if (input1->length != input2->length) return 0;

   long i,j;

   for (i = 0; i < input1->length; i++)
   {
      for (j = 0; j < ABS(input1->coeffs[i*(input1->limbs+1)])+1; j++)
      {
         if (input1->coeffs[i*(input1->limbs+1)+j] != input2->coeffs[i*(input2->limbs+1)+j])
            return 0;
      }
   }
   return 1;
}
