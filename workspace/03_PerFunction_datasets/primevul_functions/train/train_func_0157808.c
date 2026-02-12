png_icc_check_header(png_const_structrp png_ptr, png_colorspacerp colorspace,
    png_const_charp name, png_uint_32 profile_length,
    png_const_bytep profile, int color_type)
{
   png_uint_32 temp;


   temp = png_get_uint_32(profile);
   if (temp != profile_length)
      return png_icc_profile_error(png_ptr, colorspace, name, temp,
          "length does not match profile");

   temp = (png_uint_32) (*(profile+8));
   if (temp > 3 && (profile_length & 3))
      return png_icc_profile_error(png_ptr, colorspace, name, profile_length,
          "invalid length");

   temp = png_get_uint_32(profile+128);
   if (temp > 357913930 ||
      profile_length < 132+12*temp)
      return png_icc_profile_error(png_ptr, colorspace, name, temp,
          "tag count too large");


   temp = png_get_uint_32(profile+64);
   if (temp >= 0xffff)
      return png_icc_profile_error(png_ptr, colorspace, name, temp,
          "invalid rendering intent");


   if (temp >= PNG_sRGB_INTENT_LAST)
      (void)png_icc_profile_error(png_ptr, NULL, name, temp,
          "intent outside defined range");


   temp = png_get_uint_32(profile+36);
   if (temp != 0x61637370)
      return png_icc_profile_error(png_ptr, colorspace, name, temp,
          "invalid signature");


   if (memcmp(profile+68, D50_nCIEXYZ, 12) != 0)
      (void)png_icc_profile_error(png_ptr, NULL, name, 0,
          "PCS illuminant is not D50");


   temp = png_get_uint_32(profile+16);
   switch (temp)
   {
      case 0x52474220:
         if ((color_type & PNG_COLOR_MASK_COLOR) == 0)
            return png_icc_profile_error(png_ptr, colorspace, name, temp,
                "RGB color space not permitted on grayscale PNG");
         break;

      case 0x47524159:
         if ((color_type & PNG_COLOR_MASK_COLOR) != 0)
            return png_icc_profile_error(png_ptr, colorspace, name, temp,
                "Gray color space not permitted on RGB PNG");
         break;

      default:
         return png_icc_profile_error(png_ptr, colorspace, name, temp,
             "invalid ICC profile color space");
   }


   temp = png_get_uint_32(profile+12);
   switch (temp)
   {
      case 0x73636e72:
      case 0x6d6e7472:
      case 0x70727472:
      case 0x73706163:

         break;

      case 0x61627374:

         return png_icc_profile_error(png_ptr, colorspace, name, temp,
             "invalid embedded Abstract ICC profile");

      case 0x6c696e6b:


         return png_icc_profile_error(png_ptr, colorspace, name, temp,
             "unexpected DeviceLink ICC profile class");

      case 0x6e6d636c:


         (void)png_icc_profile_error(png_ptr, NULL, name, temp,
             "unexpected NamedColor ICC profile class");
         break;

      default:


         (void)png_icc_profile_error(png_ptr, NULL, name, temp,
             "unrecognized ICC profile class");
         break;
   }


   temp = png_get_uint_32(profile+20);
   switch (temp)
   {
      case 0x58595a20:
      case 0x4c616220:
         break;

      default:
         return png_icc_profile_error(png_ptr, colorspace, name, temp,
             "unexpected ICC PCS encoding");
   }

   return 1;
}
