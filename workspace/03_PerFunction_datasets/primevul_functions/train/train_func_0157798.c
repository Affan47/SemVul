png_compare_ICC_profile_with_sRGB(png_const_structrp png_ptr,
    png_const_bytep profile, uLong adler)
{


   png_uint_32 length = 0;
   png_uint_32 intent = 0x10000;
#if PNG_sRGB_PROFILE_CHECKS > 1
   uLong crc = 0;
#endif
   unsigned int i;

#ifdef PNG_SET_OPTION_SUPPORTED

   if (((png_ptr->options >> PNG_SKIP_sRGB_CHECK_PROFILE) & 3) ==
               PNG_OPTION_ON)
      return 0;
#endif

   for (i=0; i < (sizeof png_sRGB_checks) / (sizeof png_sRGB_checks[0]); ++i)
   {
      if (png_get_uint_32(profile+84) == png_sRGB_checks[i].md5[0] &&
         png_get_uint_32(profile+88) == png_sRGB_checks[i].md5[1] &&
         png_get_uint_32(profile+92) == png_sRGB_checks[i].md5[2] &&
         png_get_uint_32(profile+96) == png_sRGB_checks[i].md5[3])
      {


#        if PNG_sRGB_PROFILE_CHECKS == 0
            if (png_sRGB_checks[i].have_md5 != 0)
               return 1+png_sRGB_checks[i].is_broken;
#        endif


         if (length == 0)
         {
            length = png_get_uint_32(profile);
            intent = png_get_uint_32(profile+64);
         }


         if (length == (png_uint_32) png_sRGB_checks[i].length &&
            intent == (png_uint_32) png_sRGB_checks[i].intent)
         {

            if (adler == 0)
            {
               adler = adler32(0, NULL, 0);
               adler = adler32(adler, profile, length);
            }

            if (adler == png_sRGB_checks[i].adler)
            {


#              if PNG_sRGB_PROFILE_CHECKS > 1
                  if (crc == 0)
                  {
                     crc = crc32(0, NULL, 0);
                     crc = crc32(crc, profile, length);
                  }


                  if (crc == png_sRGB_checks[i].crc)
#              endif
               {
                  if (png_sRGB_checks[i].is_broken != 0)
                  {


                     png_chunk_report(png_ptr, "known incorrect sRGB profile",
                         PNG_CHUNK_ERROR);
                  }


                  else if (png_sRGB_checks[i].have_md5 == 0)
                  {
                     png_chunk_report(png_ptr,
                         "out-of-date sRGB profile with no signature",
                         PNG_CHUNK_WARNING);
                  }

                  return 1+png_sRGB_checks[i].is_broken;
               }
            }

# if PNG_sRGB_PROFILE_CHECKS > 0


         png_chunk_report(png_ptr,
             "Not recognizing known sRGB profile that has been edited",
             PNG_CHUNK_WARNING);
         break;
# endif
         }
      }
   }

   return 0;
}
