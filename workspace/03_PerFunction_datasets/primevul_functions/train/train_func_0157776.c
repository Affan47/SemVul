png_build_gamma_table(png_structrp png_ptr, int bit_depth)
{
   png_debug(1, "in png_build_gamma_table");


   if (png_ptr->gamma_table != NULL || png_ptr->gamma_16_table != NULL)
   {
      png_warning(png_ptr, "gamma table being rebuilt");
      png_destroy_gamma_table(png_ptr);
   }

   if (bit_depth <= 8)
   {
      png_build_8bit_table(png_ptr, &png_ptr->gamma_table,
          png_ptr->screen_gamma > 0 ?
          png_reciprocal2(png_ptr->colorspace.gamma,
          png_ptr->screen_gamma) : PNG_FP_1);

#if defined(PNG_READ_BACKGROUND_SUPPORTED) || \
   defined(PNG_READ_ALPHA_MODE_SUPPORTED) || \
   defined(PNG_READ_RGB_TO_GRAY_SUPPORTED)
      if ((png_ptr->transformations & (PNG_COMPOSE | PNG_RGB_TO_GRAY)) != 0)
      {
         png_build_8bit_table(png_ptr, &png_ptr->gamma_to_1,
             png_reciprocal(png_ptr->colorspace.gamma));

         png_build_8bit_table(png_ptr, &png_ptr->gamma_from_1,
             png_ptr->screen_gamma > 0 ?
             png_reciprocal(png_ptr->screen_gamma) :
             png_ptr->colorspace.gamma);
      }
#endif
   }
#ifdef PNG_16BIT_SUPPORTED
   else
   {
      png_byte shift, sig_bit;

      if ((png_ptr->color_type & PNG_COLOR_MASK_COLOR) != 0)
      {
         sig_bit = png_ptr->sig_bit.red;

         if (png_ptr->sig_bit.green > sig_bit)
            sig_bit = png_ptr->sig_bit.green;

         if (png_ptr->sig_bit.blue > sig_bit)
            sig_bit = png_ptr->sig_bit.blue;
      }
      else
         sig_bit = png_ptr->sig_bit.gray;


      if (sig_bit > 0 && sig_bit < 16U)

         shift = (png_byte)((16U - sig_bit) & 0xff);

      else
         shift = 0;

      if ((png_ptr->transformations & (PNG_16_TO_8 | PNG_SCALE_16_TO_8)) != 0)
      {


         if (shift < (16U - PNG_MAX_GAMMA_8))
            shift = (16U - PNG_MAX_GAMMA_8);
      }

      if (shift > 8U)
         shift = 8U;

      png_ptr->gamma_shift = shift;


      if ((png_ptr->transformations & (PNG_16_TO_8 | PNG_SCALE_16_TO_8)) != 0)
          png_build_16to8_table(png_ptr, &png_ptr->gamma_16_table, shift,
          png_ptr->screen_gamma > 0 ? png_product2(png_ptr->colorspace.gamma,
          png_ptr->screen_gamma) : PNG_FP_1);

      else
          png_build_16bit_table(png_ptr, &png_ptr->gamma_16_table, shift,
          png_ptr->screen_gamma > 0 ? png_reciprocal2(png_ptr->colorspace.gamma,
          png_ptr->screen_gamma) : PNG_FP_1);

#if defined(PNG_READ_BACKGROUND_SUPPORTED) || \
   defined(PNG_READ_ALPHA_MODE_SUPPORTED) || \
   defined(PNG_READ_RGB_TO_GRAY_SUPPORTED)
      if ((png_ptr->transformations & (PNG_COMPOSE | PNG_RGB_TO_GRAY)) != 0)
      {
         png_build_16bit_table(png_ptr, &png_ptr->gamma_16_to_1, shift,
             png_reciprocal(png_ptr->colorspace.gamma));


         png_build_16bit_table(png_ptr, &png_ptr->gamma_16_from_1, shift,
             png_ptr->screen_gamma > 0 ? png_reciprocal(png_ptr->screen_gamma) :
             png_ptr->colorspace.gamma);
      }
#endif
   }
#endif
}
