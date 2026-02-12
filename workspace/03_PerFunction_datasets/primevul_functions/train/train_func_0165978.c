int inflate_stored()

{
  unsigned n;
  unsigned w;
  register ulg b;
  register unsigned k;


  b = bb;
  k = bk;
  w = wp;


  n = k & 7;
  DUMPBITS(n);


  NEEDBITS(16)
  n = ((unsigned)b & 0xffff);
  DUMPBITS(16)
  NEEDBITS(16)
  if (n != (unsigned)((~b) & 0xffff))
    return 1;
  DUMPBITS(16)


  while (n--)
  {
    NEEDBITS(8)
    slide[w++] = (uch)b;
    if (w == WSIZE)
    {
      flush_output(w);
      w = 0;
    }
    DUMPBITS(8)
  }


  wp = w;
  bb = b;
  bk = k;
  return 0;
}
