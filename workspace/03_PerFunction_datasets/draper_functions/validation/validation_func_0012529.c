read_meta_string(bgav_input_context_t * input,
                               chunk_header_t * h)
  {
  char * ret;
  ret = calloc(h->size+1, 1);
  if(bgav_input_read_data(input, (uint8_t*)ret, h->size) < h->size)
    {
    free(ret);
    return NULL;
    }
  if(h->size & 1)
    bgav_input_skip(input, 1);
  return ret;
  }
