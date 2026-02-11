mpcandi_t_add_candidate (mpcandi_t *n, mpz_t c, const char *cpExpr,
			 int primetest)
{
#if defined (CANDI_DEBUG)
  Candi_Validate("Pre mpcandi_t_add_candidate", n);
#endif

  if (n->cpExpr)
    free (n->cpExpr);
  n->cpExpr = NULL;
  if (cpExpr)
    {
      n->nexprlen = strlen (cpExpr);
      n->cpExpr = (char *) malloc (n->nexprlen + 1);
      if (n->cpExpr == NULL)
        {
          fprintf (stderr, "Error: not enough memory\n");
          exit (EXIT_FAILURE);
        }
      strcpy (n->cpExpr, cpExpr);
    }
  mpz_set (n->n, c);
  if (primetest)
    n->isPrp = probab_prime_p (c, PROBAB_PRIME_TESTS);
  else
    n->isPrp = 0;

  n->ndigits = nb_digits (c);

#if defined (CANDI_DEBUG)
  Candi_Validate("Post mpcandi_t_add_candidate", n);
#endif

  return 1;
}
