mark_free_var_term(struct term *v,
			       struct term *t)
{
  struct rel *r;
  struct term *t1;

  if (t->type != COMPLEX)
    return;
  else {
    r = t->farg;
    for (r = t->farg; r; r = r->narg) {
      t1 = r->argval;
      if (t1->type == NAME) {
	if (t1->sym_num == v->sym_num) {
	  t1->type = VARIABLE;


	  t1->varnum = t1->sym_num;
	}
      }
      else
	mark_free_var_term(v, t1);
    }
  }
}
