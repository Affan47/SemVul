gets_past_00 (char *tok, FILE *input_FILE)
{
  int got = 0;
  int c;
  do
    {
      do
	{
	  got++;
	  c = getc (input_FILE);
	  *tok++ = c;
	}
      while (c > 0);
      got++;
      c = getc (input_FILE);
      *tok++ = c;
    }
  while (c > 0);
  return got - 2;
}
