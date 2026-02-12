png_exp(png_fixed_point x)
{
   if (x > 0 && x <= 0xfffff)
   {

      png_uint_32 e = png_32bit_exp[(x >> 12) & 0x0f];


      if (x & 0x800)
         e -= (((e >> 16) * 44938U) +  16U) >> 5;

      if (x & 0x400)
         e -= (((e >> 16) * 45181U) +  32U) >> 6;

      if (x & 0x200)
         e -= (((e >> 16) * 45303U) +  64U) >> 7;

      if (x & 0x100)
         e -= (((e >> 16) * 45365U) + 128U) >> 8;

      if (x & 0x080)
         e -= (((e >> 16) * 45395U) + 256U) >> 9;

      if (x & 0x040)
         e -= (((e >> 16) * 45410U) + 512U) >> 10;


      e -= (((e >> 16) * 355U * (x & 0x3fU)) + 256U) >> 9;


      e >>= x >> 16;
      return e;
   }


   if (x <= 0)
      return png_32bit_exp[0];


   return 0;
}
