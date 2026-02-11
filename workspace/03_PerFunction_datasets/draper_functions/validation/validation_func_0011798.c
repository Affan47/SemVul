negprop_find_near_recurse(void **p, Term query, int pos, int n)
{
  int i = (pos == 0 ? Domain_size : VARNUM(ARG(query, n)));
  if (ARITY(query) == n+1)
    return (Term) p[i];
  else
    return negprop_find_near_recurse(p[i], query, pos-1, n+1);
}
