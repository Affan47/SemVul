png_set_sPLT(png_const_structrp png_ptr,
    png_inforp info_ptr, png_const_sPLT_tp entries, int nentries)


{
   png_sPLT_tp np;

   if (png_ptr == NULL || info_ptr == NULL || nentries <= 0 || entries == NULL)
      return;


   np = png_voidcast(png_sPLT_tp,png_realloc_array(png_ptr,
      info_ptr->splt_palettes, info_ptr->splt_palettes_num, nentries,
      sizeof *np));

   if (np == NULL)
   {

      png_chunk_report(png_ptr, "too many sPLT chunks", PNG_CHUNK_WRITE_ERROR);

      return;
   }

   png_free(png_ptr, info_ptr->splt_palettes);
   info_ptr->splt_palettes = np;
   info_ptr->free_me |= PNG_FREE_SPLT;

   np += info_ptr->splt_palettes_num;

   do
   {
      png_size_t length;


      if (entries->name == NULL || entries->entries == NULL)
      {

         png_app_error(png_ptr, "png_set_sPLT: invalid sPLT");

         continue;
      }

      np->depth = entries->depth;


      length = strlen(entries->name) + 1;
      np->name = png_voidcast(png_charp, png_malloc_base(png_ptr, length));

      if (np->name == NULL)
         break;

      memcpy(np->name, entries->name, length);


      np->entries = png_voidcast(png_sPLT_entryp, png_malloc_array(png_ptr,
          entries->nentries, sizeof (png_sPLT_entry)));

      if (np->entries == NULL)
      {
         png_free(png_ptr, np->name);
         np->name = NULL;
         break;
      }

      np->nentries = entries->nentries;


      memcpy(np->entries, entries->entries,
         entries->nentries * sizeof (png_sPLT_entry));


      info_ptr->valid |= PNG_INFO_sPLT;
      ++(info_ptr->splt_palettes_num);
      ++np;
   }
   while (++entries, --nentries);

   if (nentries > 0)
      png_chunk_report(png_ptr, "sPLT out of memory", PNG_CHUNK_WRITE_ERROR);
}
