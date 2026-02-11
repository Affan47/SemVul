proof_length(struct clause *c)
{
  struct clause_ptr *cp1, *cp2;
  struct ilist *ip1, *ip2;
  int count, level;

  cp1 = NULL; ip1 = NULL;
  level = get_ancestors(c, &cp1, &ip1);

  for (count = 0; cp1; ) {
    if (cp1->c->parents && cp1->c->parents->i != NEW_DEMOD_RULE)
      count++;
    cp2 = cp1; cp1 = cp1->next; free_clause_ptr(cp2);
    ip2 = ip1; ip1 = ip1->next; free_ilist(ip2);
  }
  return(count);
}
