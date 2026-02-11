neg_clauses_and_descendants(Plist proof,
				  Clist a_list, Clist b_list, Clist c_list)
{
  Topform first_neg = first_negative_clause(proof);
  Plist descendents = plist_prepend(NULL, first_neg);
  Plist p;


  Clist_pos a = a_list->first;
  Clist_pos b = b_list->first;
  Clist_pos c = c_list->first;

  Topform next = next_negative_clause_3(&a, &b, &c);
  while (next) {
    Topform neg_parent = first_negative_parent(next);
    if (neg_parent && clause_plist_member(descendents, neg_parent, FALSE))
      descendents = insert_clause_into_plist(descendents, next, FALSE);
    next = next_negative_clause_3(&a, &b, &c);
  }


  for (p = proof; p; p = p->next) {
    Topform c = p->v;
    if (!c->is_formula && negative_clause(c->literals))

      descendents = insert_clause_into_plist(descendents, c, FALSE);
  }

  descendents = reverse_plist(descendents);

#if 1
  {
    int n = 0;
    printf("\n%% Preparing to disable descendents of clause %d:",
	   first_neg->id);
    for (p = descendents; p; p = p->next) {
      printf(" %d", ((Topform) p->v)->id);
      if (++n % 20 == 0)
	printf("\n");
    }
    printf("\n");
  }
#endif

  return descendents;
}
