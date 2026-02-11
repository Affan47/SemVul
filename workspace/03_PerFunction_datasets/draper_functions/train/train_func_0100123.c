yualtschul_scorematrix_validate(const ESL_SCOREMATRIX *S)
{
  int i, j;
  int has_neg, has_pos;


  for (i = 0; i < S->K; i++)
    {
      has_neg = has_pos = FALSE;
      for (j = 0; j < S->K; j++)
	{
	  if (S->s[i][j] > 0) has_pos = TRUE;
	  if (S->s[i][j] < 0) has_neg = TRUE;
	}
      if (! has_pos || ! has_neg) return eslFAIL;
    }


  for (j = 0; j < S->K; j++)
    {
      has_neg = has_pos = FALSE;
      for (i = 0; i < S->K; i++)
	{
	  if (S->s[i][j] > 0) has_pos = TRUE;
	  if (S->s[i][j] < 0) has_neg = TRUE;
	}
      if (! has_pos || ! has_neg) return eslFAIL;
    }

  return eslOK;
}
