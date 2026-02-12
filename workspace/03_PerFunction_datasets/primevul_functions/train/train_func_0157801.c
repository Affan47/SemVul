png_log8bit(unsigned int x)
{
   unsigned int lg2 = 0;


   if ((x &= 0xff) == 0)
      return -1;

   if ((x & 0xf0) == 0)
      lg2  = 4, x <<= 4;

   if ((x & 0xc0) == 0)
      lg2 += 2, x <<= 2;

   if ((x & 0x80) == 0)
      lg2 += 1, x <<= 1;


   return (png_int_32)((lg2 << 16) + ((png_8bit_l2[x-128]+32768)>>16));
}
