png_handle_sRGB(png_structp png_ptr, png_infop info_ptr, png_uint_32 length)
{
   int intent;
   png_byte buf[1];

   png_debug(1, "in png_handle_sRGB");

   if (!(png_ptr->mode & PNG_HAVE_IHDR))
      png_error(png_ptr, "Missing IHDR before sRGB");

   else if (png_ptr->mode & PNG_HAVE_IDAT)
   {
      png_warning(png_ptr, "Invalid sRGB after IDAT");
      png_crc_finish(png_ptr, length);
      return;
   }

   else if (png_ptr->mode & PNG_HAVE_PLTE)

      png_warning(png_ptr, "Out of place sRGB chunk");

   if (info_ptr != NULL && (info_ptr->valid & PNG_INFO_sRGB))
   {
      png_warning(png_ptr, "Duplicate sRGB chunk");
      png_crc_finish(png_ptr, length);
      return;
   }

   if (length != 1)
   {
      png_warning(png_ptr, "Incorrect sRGB chunk length");
      png_crc_finish(png_ptr, length);
      return;
   }

   png_crc_read(png_ptr, buf, 1);

   if (png_crc_finish(png_ptr, 0))
      return;

   intent = buf[0];


   if (intent >= PNG_sRGB_INTENT_LAST)
   {
      png_warning(png_ptr, "Unknown sRGB intent");
      return;
   }

#if defined(PNG_READ_gAMA_SUPPORTED) && defined(PNG_READ_GAMMA_SUPPORTED)
   if (info_ptr != NULL && (info_ptr->valid & PNG_INFO_gAMA))
   {
      if (PNG_OUT_OF_RANGE(info_ptr->gamma, 45500, 500))
      {
         PNG_WARNING_PARAMETERS(p)

         png_warning_parameter_signed(p, 1, PNG_NUMBER_FORMAT_fixed,
            info_ptr->gamma);

         png_formatted_warning(png_ptr, p,
             "Ignoring incorrect gAMA value @1 when sRGB is also present");
      }
   }
#endif

#ifdef PNG_READ_cHRM_SUPPORTED
   if (info_ptr != NULL && (info_ptr->valid & PNG_INFO_cHRM))
      if (PNG_OUT_OF_RANGE(info_ptr->x_white, 31270,  1000) ||
          PNG_OUT_OF_RANGE(info_ptr->y_white, 32900,  1000) ||
          PNG_OUT_OF_RANGE(info_ptr->x_red,   64000,  1000) ||
          PNG_OUT_OF_RANGE(info_ptr->y_red,   33000,  1000) ||
          PNG_OUT_OF_RANGE(info_ptr->x_green, 30000,  1000) ||
          PNG_OUT_OF_RANGE(info_ptr->y_green, 60000,  1000) ||
          PNG_OUT_OF_RANGE(info_ptr->x_blue,  15000,  1000) ||
          PNG_OUT_OF_RANGE(info_ptr->y_blue,   6000,  1000))
      {
         png_warning(png_ptr,
             "Ignoring incorrect cHRM value when sRGB is also present");
      }
#endif


   png_ptr->is_sRGB = 1;

#  ifdef PNG_READ_RGB_TO_GRAY_SUPPORTED

      if (!png_ptr->rgb_to_gray_coefficients_set)
      {


         png_ptr->rgb_to_gray_red_coeff   =  6968;
         png_ptr->rgb_to_gray_green_coeff = 23434;


         png_ptr->rgb_to_gray_coefficients_set = 1;
      }
#  endif

   png_set_sRGB_gAMA_and_cHRM(png_ptr, info_ptr, intent);
}
