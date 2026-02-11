hgcd_ref_equal (const struct hgcd_ref *A, const struct hgcd_ref *B)
{
  unsigned i;

  for (i = 0; i<2; i++)
    {
      unsigned j;

      for (j = 0; j<2; j++)
	if (mpz_cmp (A->m[i][j], B->m[i][j]) != 0)
	  return 0;
    }

  return 1;
}
