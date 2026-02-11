mailstream_new(mailstream_low * low, size_t buffer_size)
{
  mailstream * s;

  s = malloc(sizeof(* s));
  if (s == NULL)
    goto err;

  s->read_buffer = malloc(buffer_size);
  if (s->read_buffer == NULL)
    goto free_s;
  s->read_buffer_len = 0;

  s->write_buffer = malloc(buffer_size);
  if (s->write_buffer == NULL)
    goto free_read_buffer;
  s->write_buffer_len = 0;

  s->buffer_max_size = buffer_size;
  s->low = low;

  return s;

 free_read_buffer:
  free(s->read_buffer);
 free_s:
  free(s);
 err:
  return NULL;
}
