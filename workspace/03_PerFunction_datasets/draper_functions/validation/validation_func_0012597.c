clausify_formula_list(struct formula_ptr *fp)
{
  struct list *l, *l1;
  struct formula_ptr *fp1, *fp2;

  l = get_list();
  fp1 = fp;
  while (fp1 != NULL) {
    if (Flags[FORMULA_HISTORY].val) {
      int f_id;
      struct clause *c = get_clause();
      struct literal *lit = get_literal();
      struct ilist *ip1 = get_ilist();
      struct ilist *ip2 = get_ilist();
      c->first_lit = lit;
      lit->sign = 1;
      lit->atom = formula_to_term(fp1->f);
      assign_cl_id(c);
      f_id = c->id;
      hide_clause(c);

      l1 = clausify(fp1->f);

      for (c = l1->first_cl; c; c = c->next_cl) {
	ip1 = get_ilist();
	ip2 = get_ilist();
	c->parents = ip1;
	ip1->next = ip2;
	ip1->i = CLAUSIFY_RULE;
	ip2->i = f_id;
      }
    }
    else
      l1 = clausify(fp1->f);

    append_lists(l, l1);
    fp2 = fp1;
    fp1 = fp1->next;
    free_formula_ptr(fp2);
  }
  return(l);
}
