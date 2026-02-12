png_icc_profile_error(png_const_structrp png_ptr, png_colorspacerp colorspace,
    png_const_charp name, png_alloc_size_t value, png_const_charp reason)
{
   size_t pos;
   char message[196];

   if (colorspace != NULL)
      colorspace->flags |= PNG_COLORSPACE_INVALID;

   pos = png_safecat(message, (sizeof message), 0, "profile '");
   pos = png_safecat(message, pos+79, pos, name);
   pos = png_safecat(message, (sizeof message), pos, "': ");
   if (is_ICC_signature(value) != 0)
   {

      png_icc_tag_name(message+pos, (png_uint_32)value);
      pos += 6;
      message[pos++] = ':';
      message[pos++] = ' ';
   }
#  ifdef PNG_WARNINGS_SUPPORTED
   else
      {
         char number[PNG_NUMBER_BUFFER_SIZE];

         pos = png_safecat(message, (sizeof message), pos,
             png_format_number(number, number+(sizeof number),
             PNG_NUMBER_FORMAT_x, value));
         pos = png_safecat(message, (sizeof message), pos, "h: ");
      }
#  endif

   pos = png_safecat(message, (sizeof message), pos, reason);
   PNG_UNUSED(pos)


   png_chunk_report(png_ptr, message,
       (colorspace != NULL) ? PNG_CHUNK_ERROR : PNG_CHUNK_WRITE_ERROR);

   return 0;
}
