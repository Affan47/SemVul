lto_write_stream (struct lto_output_stream *obs)
{
  unsigned int block_size = 1024;
  struct lto_char_ptr_base *block;
  struct lto_char_ptr_base *next_block;
  if (!obs->first_block)
    return;

  for (block = obs->first_block; block; block = next_block)
    {
      const char *base = ((char *)block) + sizeof (struct lto_char_ptr_base);
      unsigned int num_chars = block_size - sizeof (struct lto_char_ptr_base);


      next_block = (struct lto_char_ptr_base *) block->ptr;
      if (!next_block)
	num_chars -= obs->left_in_block;


      if (compression_stream)
	{
	  lto_compress_block (compression_stream, base, num_chars);
	  lang_hooks.lto.append_data (NULL, 0, block);
	}
      else
	lang_hooks.lto.append_data (base, num_chars, block);
      block_size *= 2;
    }
}
