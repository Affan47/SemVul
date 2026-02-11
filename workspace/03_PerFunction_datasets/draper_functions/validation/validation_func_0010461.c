translate_linestrip_ushort2uint_last2first(
    const void * _in,
    unsigned start,
    unsigned nr,
    void *_out )
{
  const ushort*in = (const ushort*)_in;
  uint *out = (uint*)_out;
  unsigned i, j;
  (void)j;
  for (i = start, j = 0; j < nr; j+=2, i++) {
      (out+j)[0] = (uint)in[i+1];
      (out+j)[1] = (uint)in[i];
   }
}
