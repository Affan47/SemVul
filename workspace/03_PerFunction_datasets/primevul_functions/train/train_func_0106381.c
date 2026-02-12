png_set_unknown_chunks(png_const_structrp png_ptr,
   png_inforp info_ptr, png_const_unknown_chunkp unknowns, int num_unknowns)
{
   png_unknown_chunkp np;

   if (png_ptr == NULL || info_ptr == NULL || num_unknowns <= 0 ||
       unknowns == NULL)
      return;


#  if !defined(PNG_READ_UNKNOWN_CHUNKS_SUPPORTED) && \
      defined(PNG_READ_SUPPORTED)
      if ((png_ptr->mode & PNG_IS_READ_STRUCT) != 0)
      {
         png_app_error(png_ptr, "no unknown chunk support on read");

         return;
      }
#  endif
#  if !defined(PNG_WRITE_UNKNOWN_CHUNKS_SUPPORTED) && \
      defined(PNG_WRITE_SUPPORTED)
      if ((png_ptr->mode & PNG_IS_READ_STRUCT) == 0)
      {
         png_app_error(png_ptr, "no unknown chunk support on write");

         return;
      }
#  endif


   np = png_voidcast(png_unknown_chunkp, png_realloc_array(png_ptr,
         info_ptr->unknown_chunks, info_ptr->unknown_chunks_num, num_unknowns,
         sizeof *np));

   if (np == NULL)
   {
      png_chunk_report(png_ptr, "too many unknown chunks",
         PNG_CHUNK_WRITE_ERROR);

      return;
   }

   png_free(png_ptr, info_ptr->unknown_chunks);
   info_ptr->unknown_chunks = np;
   info_ptr->free_me |= PNG_FREE_UNKN;

   np += info_ptr->unknown_chunks_num;


   for (; num_unknowns > 0; --num_unknowns, ++unknowns)
   {
      memcpy(np->name, unknowns->name, (sizeof np->name));
      np->name[(sizeof np->name)-1] = '\0';
      np->location = check_location(png_ptr, unknowns->location);

      if (unknowns->size == 0)
      {
         np->data = NULL;
         np->size = 0;
      }

      else
      {
         np->data = png_voidcast(png_bytep,
            png_malloc_base(png_ptr, unknowns->size));

         if (np->data == NULL)
         {
            png_chunk_report(png_ptr, "unknown chunk: out of memory",
               PNG_CHUNK_WRITE_ERROR);

            continue;
         }

         memcpy(np->data, unknowns->data, unknowns->size);
         np->size = unknowns->size;
      }


      ++np;
      ++(info_ptr->unknown_chunks_num);
   }
}
