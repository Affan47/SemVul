generate_linestrip_ushort_first2last(
    unsigned start,
    unsigned nr,
    void *_out )
{
  ushort *out = (ushort*)_out;
  unsigned i, j;
  (void)j;
  for (i = start, j = 0; j < nr; j+=2, i++) {
      (out+j)[0] = (ushort)(i+1);
      (out+j)[1] = (ushort)(i);
   }
}
