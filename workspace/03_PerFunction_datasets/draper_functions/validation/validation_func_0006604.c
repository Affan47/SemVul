vbitset_xor (bitset dst, bitset src1, bitset src2)
{
  unsigned int i;
  bitset_word *src1p;
  bitset_word *src2p;
  bitset_word *dstp;
  bitset_windex ssize1;
  bitset_windex ssize2;
  bitset_windex dsize;

  vbitset_resize (dst, max (BITSET_SIZE_ (src1), BITSET_SIZE_ (src2)));

  dsize = VBITSET_SIZE (dst);
  ssize1 = VBITSET_SIZE (src1);
  ssize2 = VBITSET_SIZE (src2);
  dstp = VBITSET_WORDS (dst);
  src1p = VBITSET_WORDS (src1);
  src2p = VBITSET_WORDS (src2);

  for (i = 0; i < min (ssize1, ssize2); i++)
      *dstp++ = *src1p++ ^ *src2p++;

  if (ssize2 > ssize1)
    {
      src1p = src2p;
      ssize1 = ssize2;
    }

  for (; i < ssize1; i++)
    *dstp++ = *src1p++;

  memset (dstp, 0, sizeof (bitset_word) * (dsize - ssize1));
}
