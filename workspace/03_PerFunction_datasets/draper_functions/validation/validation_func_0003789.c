subst_domain_elements_term(Term t, int *vals)
{
  if (VARIABLE(t)) {
    Term t2 = Domain[vals[VARNUM(t)]];
    zap_term(t);
    return t2;
  }
  else {
    int i;
    i = natural_constant_term(t);
    if (i >= 0) {
      zap_term(t);
      if (i < Domain_size)
	return Domain[i];
      else
	return get_variable_term(i);
    }
    else {
      for (i = 0; i < ARITY(t); i++)
	ARG(t,i) = subst_domain_elements_term(ARG(t,i), vals);
      return t;
    }
  }
}
