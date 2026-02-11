zeroset(s)
     charclass s;
{
  int i;

  for (i = 0; i < CHARCLASS_INTS; ++i)
    s[i] = 0;
}
