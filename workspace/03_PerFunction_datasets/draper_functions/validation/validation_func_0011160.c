GCGchecksum(char *seq, int len)
{
  int i;
  int chk = 0;

  for (i = 0; i < len; i++)
    chk = (chk + (i % 57 + 1) * (sre_toupper((int) seq[i]))) % 10000;
  return chk;
}
