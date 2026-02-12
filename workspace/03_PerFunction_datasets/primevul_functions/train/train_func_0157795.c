png_exp16bit(png_fixed_point lg2)
{

   png_uint_32 x = png_exp(lg2);


   x -= x >> 16;
   return (png_uint_16)((x + 32767U) >> 16);
}
