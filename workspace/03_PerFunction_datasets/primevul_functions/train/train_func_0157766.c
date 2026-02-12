png_gamma_16bit_correct(unsigned int value, png_fixed_point gamma_val)
{
   if (value > 0 && value < 65535)
   {
# ifdef PNG_FLOATING_ARITHMETIC_SUPPORTED


      double r = floor(65535*pow((png_int_32)value/65535.,
          gamma_val*.00001)+.5);
      return (png_uint_16)r;
# else
      png_int_32 lg2 = png_log16bit(value);
      png_fixed_point res;

      if (png_muldiv(&res, gamma_val, lg2, PNG_FP_1) != 0)
         return png_exp16bit(res);


      value = 0;
# endif
   }

   return (png_uint_16)value;
}
