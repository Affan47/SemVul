abitset_not (bitset dst, bitset src)
{
  bitset_windex i;
  bitset_word *srcp = ABITSET_WORDS (src);
  bitset_word *dstp = ABITSET_WORDS (dst);
  bitset_windex size = dst->b.csize;

  for (i = 0; i < size; i++)
      *dstp++ = ~(*srcp++);
  abitset_unused_clear (dst);
}
