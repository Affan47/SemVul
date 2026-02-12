zalloc_cb(voidpf opaque, unsigned int items, unsigned int size)
{
  (void) opaque;

  return (voidpf) calloc(items, size);
}
