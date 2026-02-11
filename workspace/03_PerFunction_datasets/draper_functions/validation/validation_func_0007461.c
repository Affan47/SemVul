png_write_sBIT(png_structp png_ptr, png_color_8p sbit, int color_type)
{
#ifdef PNG_USE_LOCAL_ARRAYS
   PNG_sBIT;
#endif
   png_byte buf[4];
   png_size_t size;

   png_debug(1, "in png_write_sBIT");


   if (color_type & PNG_COLOR_MASK_COLOR)
   {
      png_byte maxbits;

      maxbits = (png_byte)(color_type==PNG_COLOR_TYPE_PALETTE ? 8 :
                png_ptr->usr_bit_depth);
      if (sbit->red == 0 || sbit->red > maxbits ||
          sbit->green == 0 || sbit->green > maxbits ||
          sbit->blue == 0 || sbit->blue > maxbits)
      {
         png_warning(png_ptr, "Invalid sBIT depth specified");
         return;
      }
      buf[0] = sbit->red;
      buf[1] = sbit->green;
      buf[2] = sbit->blue;
      size = 3;
   }
   else
   {
      if (sbit->gray == 0 || sbit->gray > png_ptr->usr_bit_depth)
      {
         png_warning(png_ptr, "Invalid sBIT depth specified");
         return;
      }
      buf[0] = sbit->gray;
      size = 1;
   }

   if (color_type & PNG_COLOR_MASK_ALPHA)
   {
      if (sbit->alpha == 0 || sbit->alpha > png_ptr->usr_bit_depth)
      {
         png_warning(png_ptr, "Invalid sBIT depth specified");
         return;
      }
      buf[size++] = sbit->alpha;
   }

   png_write_chunk(png_ptr, (png_bytep)png_sBIT, buf, size);
}
