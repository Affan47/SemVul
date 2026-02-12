int inflate_block(e)
int *e;

{
  unsigned t;
  unsigned w;
  register ulg b;
  register unsigned k;


  b = bb;
  k = bk;
  w = wp;


  NEEDBITS(1)
  *e = (int)b & 1;
  DUMPBITS(1)


  NEEDBITS(2)
  t = (unsigned)b & 3;
  DUMPBITS(2)


  bb = b;
  bk = k;


  if (t == 2)
    return inflate_dynamic();
  if (t == 0)
    return inflate_stored();
  if (t == 1)
    return inflate_fixed();


  return 2;
}
