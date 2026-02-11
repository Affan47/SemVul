eprn_bits_for_levels(unsigned int levels)
{
  unsigned int bits = 0;
  unsigned long n;

  for (n = 1; n < levels; n *= 2) bits++;

  return bits;
}
