ZmodF_mul_info_init_fft(ZmodF_mul_info_t info, unsigned long n,
                             unsigned long depth, unsigned long m,
                             unsigned long k, int squaring)
{
   FLINT_ASSERT((n * FLINT_BITS) % (1 << depth) == 0);
   FLINT_ASSERT(k <= m);

   info->algo = ZMODF_MUL_ALGO_FFT;
   info->n = n;
   info->squaring = squaring;

   if (!m)
   {


      unsigned long input_bits = (n*FLINT_BITS) >> depth;
      unsigned long output_bits = 2*input_bits + 1 + depth;
      m = ((output_bits - 1) >> FLINT_LG_BITS_PER_LIMB) + 1;
      k = 0;


      unsigned long shift = 0;
      if (depth > FLINT_LG_BITS_PER_LIMB)
         shift = depth - FLINT_LG_BITS_PER_LIMB;


      if (m < ZmodF_mul_threeway_fft_threshold)
      {


         unsigned long smaller_m = (m / 3) * 3;
         if (((smaller_m >> shift) << shift) == smaller_m)
         {
            k = m - smaller_m;
            m = smaller_m;
         }
         else
         {

            unsigned long round = 3 << shift;
            m = (((m-1) / round) + 1) * round;
         }
      }
      else
      {


         unsigned long smaller_m = (m >> shift) << shift;
         if (m - smaller_m <= 2)
         {
            k = m - smaller_m;
            m = smaller_m;
         }
         else
         {

            m = (((m - 1) >> shift) + 1) << shift;
         }
      }
   }

   FLINT_ASSERT((m*FLINT_BITS) % (1 << depth) == 0);
   FLINT_ASSERT(k <= 2);
   FLINT_ASSERT((m+k)*FLINT_BITS >= ((2*n*FLINT_BITS) >> depth) + 1 + depth);
   info->m = m;
   info->k = k;


   ZmodF_poly_init(info->polys[0], depth, m + k, 1);
   ZmodF_poly_decrease_n(info->polys[0], m);

   if (!squaring)
   {
      ZmodF_poly_init(info->polys[1], depth, m + k, 1);
      ZmodF_poly_decrease_n(info->polys[1], m);
   }


   if (k)
      info->scratch = (mp_limb_t*) flint_heap_alloc((3*k) << depth);
   else
      info->scratch = NULL;
}
