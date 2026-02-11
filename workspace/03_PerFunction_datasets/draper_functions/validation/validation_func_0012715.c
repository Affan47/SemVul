eval_formula(Formula f, Interp p)
{
  int a[MAX_VARS_EVAL], *vals;
  int nsyms, i;
  BOOL rc;

  nsyms = greatest_symnum_in_formula(f) + 1;
  if (nsyms > MAX_VARS_EVAL)
    vals = malloc((nsyms * sizeof(int)));
  else
    vals = a;

  for (i = 0; i < nsyms; i++)
    vals[i] = -1;

  rc = eval_form(f, p, vals);

  if (nsyms > MAX_VARS_EVAL)
    free(vals);

#if 0
  if (rc)
    printf("Formula is TRUE in this interpretation.\n");
  else {
    printf("Formula is FALSE in this interpretation.\n");
  }
#endif
  return rc;
}
