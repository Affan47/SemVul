PairwiseIdentity(char *s1, char *s2)
{
  int     idents;
  int     len1, len2;
  int     x;

  idents = len1 = len2 = 0;
  for (x = 0; s1[x] != '\0' && s2[x] != '\0'; x++)
    {
#ifdef CLUSTALO
      char c1 = toupper(s1[x]);
      char c2 = toupper(s2[x]);
      if (c1=='U')
          c1 = 'T';
      if (c2=='U')
          c2 = 'T';

      if (!isgap(c1)) {
          len1++;
          if (c1 == c2)
              idents++;
      }
      if (!isgap(c2))
          len2++;
#else
      if (!isgap(s1[x])) {
	len1++;
	if (s1[x] == s2[x]) idents++;
      }
      if (!isgap(s2[x])) len2++;
#endif
    }
  if (len2 < len1) len1 = len2;
  return (len1 == 0 ? 0.0 : (float) idents / (float) len1);
}
