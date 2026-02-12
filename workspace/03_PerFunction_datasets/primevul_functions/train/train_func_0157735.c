png_exp8bit(png_fixed_point lg2)
{

   png_uint_32 x = png_exp(lg2);


   x -= x >> 8;
   return (png_byte)(((x + 0x7fffffU) >> 24) & 0xff);
}
