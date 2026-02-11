part_recurse(Term top, Term t, Topform demod, int target, int direction,
		  int *sequence, Ilist *ipos)
{
  if (VARIABLE(t))
    return t;
  else {
    int i;
    for (i = 0; i < ARITY(t) && *ipos == NULL; i++) {
      ARG(t,i) = part_recurse(top, ARG(t,i), demod, target,
			      direction, sequence, ipos);
    }

    if (*ipos != NULL || *sequence >= target)
      return t;
    else {
      (*sequence)++;
      if (*sequence != target)
	return t;
      else {
	Term alpha, beta;
	Context subst = get_context();
	Trail tr = NULL;
	if (direction == 1) {
	  alpha = ARG(demod->literals->atom, 0);
	  beta  = ARG(demod->literals->atom, 1);
	}
	else {
	  alpha = ARG(demod->literals->atom, 1);
	  beta  = ARG(demod->literals->atom, 0);
	}
	if (match(alpha, subst, t, &tr)) {
	  Term result = apply(beta, subst);
	  undo_subst(tr);
	  *ipos = position_of_subterm(top, t);
	  zap_term(t);
	  t = result;
	}
	else {
	  printf("demodulator%s: ", direction == 1 ? "" : " (R)");
	  fprint_clause(stdout, demod);
	  printf("target=%d: ", target); p_term(t);
	  fatal_error("part_recurse, not rewitable");
	}
	free_context(subst);
	return t;
      }
    }
  }
}
