png_set_keep_unknown_chunks(png_structrp png_ptr, int keep,
    png_const_bytep chunk_list, int num_chunks_in)
{
   png_bytep new_list;
   unsigned int num_chunks, old_num_chunks;

   if (png_ptr == NULL)
      return;

   if (keep < 0 || keep >= PNG_HANDLE_CHUNK_LAST)
   {
      png_app_error(png_ptr, "png_set_keep_unknown_chunks: invalid keep");

      return;
   }

   if (num_chunks_in <= 0)
   {
      png_ptr->unknown_default = keep;


      if (num_chunks_in == 0)
        return;
   }

   if (num_chunks_in < 0)
   {


      static PNG_CONST png_byte chunks_to_ignore[] = {
         98,  75,  71,  68, '\0',
         99,  72,  82,  77, '\0',
        103,  65,  77,  65, '\0',
        104,  73,  83,  84, '\0',
        105,  67,  67,  80, '\0',
        105,  84,  88, 116, '\0',
        111,  70,  70, 115, '\0',
        112,  67,  65,  76, '\0',
        112,  72,  89, 115, '\0',
        115,  66,  73,  84, '\0',
        115,  67,  65,  76, '\0',
        115,  80,  76,  84, '\0',
        115,  84,  69,  82, '\0',
        115,  82,  71,  66, '\0',
        116,  69,  88, 116, '\0',
        116,  73,  77,  69, '\0',
        122,  84,  88, 116, '\0'
      };

      chunk_list = chunks_to_ignore;
      num_chunks = (unsigned int)(sizeof chunks_to_ignore)/5U;
   }

   else
   {
      if (chunk_list == NULL)
      {


         png_app_error(png_ptr, "png_set_keep_unknown_chunks: no chunk list");

         return;
      }

      num_chunks = num_chunks_in;
   }

   old_num_chunks = png_ptr->num_chunk_list;
   if (png_ptr->chunk_list == NULL)
      old_num_chunks = 0;


   if (num_chunks + old_num_chunks > UINT_MAX/5)
   {
      png_app_error(png_ptr, "png_set_keep_unknown_chunks: too many chunks");

      return;
   }


   if (keep != 0)
   {
      new_list = png_voidcast(png_bytep, png_malloc(png_ptr,
          5 * (num_chunks + old_num_chunks)));

      if (old_num_chunks > 0)
         memcpy(new_list, png_ptr->chunk_list, 5*old_num_chunks);
   }

   else if (old_num_chunks > 0)
      new_list = png_ptr->chunk_list;

   else
      new_list = NULL;


   if (new_list != NULL)
   {
      png_const_bytep inlist;
      png_bytep outlist;
      unsigned int i;

      for (i=0; i<num_chunks; ++i)
      {
         old_num_chunks = add_one_chunk(new_list, old_num_chunks,
            chunk_list+5*i, keep);
      }


      num_chunks = 0;
      for (i=0, inlist=outlist=new_list; i<old_num_chunks; ++i, inlist += 5)
      {
         if (inlist[4])
         {
            if (outlist != inlist)
               memcpy(outlist, inlist, 5);
            outlist += 5;
            ++num_chunks;
         }
      }


      if (num_chunks == 0)
      {
         if (png_ptr->chunk_list != new_list)
            png_free(png_ptr, new_list);

         new_list = NULL;
      }
   }

   else
      num_chunks = 0;

   png_ptr->num_chunk_list = num_chunks;

   if (png_ptr->chunk_list != new_list)
   {
      if (png_ptr->chunk_list != NULL)
         png_free(png_ptr, png_ptr->chunk_list);

      png_ptr->chunk_list = new_list;
   }
}
