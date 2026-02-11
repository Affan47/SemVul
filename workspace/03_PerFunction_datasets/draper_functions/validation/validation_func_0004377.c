write_buffer(dest_t *dest, unsigned char *ptr, glui32 len)
{
  if (dest->ismem) {
    if (dest->pos+len > dest->size) {
      dest->size = dest->pos+len+1024;
      if (!dest->ptr) {
        dest->ptr = glulx_malloc(dest->size);
      }
      else {
        dest->ptr = glulx_realloc(dest->ptr, dest->size);
      }
      if (!dest->ptr)
        return 1;
    }
    memcpy(dest->ptr+dest->pos, ptr, len);
  }
  else {
    glk_put_buffer_stream(dest->str, (char *)ptr, len);
  }

  dest->pos += len;

  return 0;
}
