png_set_unknown_chunk_location(png_const_structrp png_ptr, png_inforp info_ptr,
    int chunk, int location)
{


   if (png_ptr != NULL && info_ptr != NULL && chunk >= 0 &&
      chunk < info_ptr->unknown_chunks_num)
   {
      if ((location & (PNG_HAVE_IHDR|PNG_HAVE_PLTE|PNG_AFTER_IDAT)) == 0)
      {
         png_app_error(png_ptr, "invalid unknown chunk location");

         if ((location & PNG_HAVE_IDAT) != 0)
            location = PNG_AFTER_IDAT;

         else
            location = PNG_HAVE_IHDR;
      }

      info_ptr->unknown_chunks[chunk].location =
         check_location(png_ptr, location);
   }
}
