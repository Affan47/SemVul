png_set_tRNS(png_structrp png_ptr, png_inforp info_ptr,
    png_const_bytep trans_alpha, int num_trans, png_const_color_16p trans_color)
{
   png_debug1(1, "in %s storage function", "tRNS");

   if (png_ptr == NULL || info_ptr == NULL)

      return;

   if (trans_alpha != NULL)
   {


       png_free_data(png_ptr, info_ptr, PNG_FREE_TRNS, 0);


       png_ptr->trans_alpha = info_ptr->trans_alpha = png_voidcast(png_bytep,
         png_malloc(png_ptr, PNG_MAX_PALETTE_LENGTH));

       if (num_trans > 0 && num_trans <= PNG_MAX_PALETTE_LENGTH)
          memcpy(info_ptr->trans_alpha, trans_alpha, (png_size_t)num_trans);
   }

   if (trans_color != NULL)
   {
#ifdef PNG_WARNINGS_SUPPORTED
      if (info_ptr->bit_depth < 16)
      {
         int sample_max = (1 << info_ptr->bit_depth) - 1;

         if ((info_ptr->color_type == PNG_COLOR_TYPE_GRAY &&
             trans_color->gray > sample_max) ||
             (info_ptr->color_type == PNG_COLOR_TYPE_RGB &&
             (trans_color->red > sample_max ||
             trans_color->green > sample_max ||
             trans_color->blue > sample_max)))
            png_warning(png_ptr,
               "tRNS chunk has out-of-range samples for bit_depth");
      }
#endif

      info_ptr->trans_color = *trans_color;

      if (num_trans == 0)
         num_trans = 1;
   }

   info_ptr->num_trans = (png_uint_16)num_trans;

   if (num_trans != 0)
   {
      info_ptr->valid |= PNG_INFO_tRNS;
      info_ptr->free_me |= PNG_FREE_TRNS;
   }
}
