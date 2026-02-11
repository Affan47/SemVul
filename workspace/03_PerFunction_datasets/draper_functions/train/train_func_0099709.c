rsym_occurrences(int symbol, Topform c)
{
  int n = 0;
  Literals lit;
  for (lit = c->literals; lit; lit = lit->next)
    if (SYMNUM(lit->atom) == symbol)
      n++;
  return n;
}
