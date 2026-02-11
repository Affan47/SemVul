zmod_poly_fread(zmod_poly_t poly, FILE* f)
{

   unsigned long length, p;

   if (!fscanf(f, "%ld %ld", &length, &p))
      return 0;

   zmod_poly_init(poly, p);

	zmod_poly_fit_length(poly, length);


   for (unsigned long i = 0; i < length; i++)
   {
      if (!fscanf(f, "%ld", &poly->coeffs[i]))
         return 0;
		poly->length++;
   }

   __zmod_poly_normalise(poly);

   return 1;
}
