addcchar (c, flag)
     unsigned char c;
     int flag;
{
  char *fstr;

  if (debug)
    {
      fstr = getcstr (flag);
      fprintf (stderr, "added %s for character %s\n", fstr, cdesc(c));
    }
  lsyntax[c] |= flag;
}
