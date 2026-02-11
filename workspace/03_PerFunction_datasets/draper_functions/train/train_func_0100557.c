esl_scorematrix_SetFromProbs(ESL_SCOREMATRIX *S, double lambda, const ESL_DMATRIX *P, const double *fi, const double *fj)
{
  int    i,j;
  double sc;

  for (i = 0; i < S->abc_r->K; i++)
    for (j = 0; j < S->abc_r->K; j++)
      {
	sc = log(P->mx[i][j] / (fi[i] * fj[j])) / lambda;
	S->s[i][j] = (int) (sc + (sc>0 ? 0.5 : -0.5));
      }

  for (i = 0; i < S->abc_r->K; i++)
    S->isval[i] = TRUE;
  S->nc = S->abc_r->K;

  strncpy(S->outorder, S->abc_r->sym, S->abc_r->K);
  S->outorder[S->nc] = '\0';
  return eslOK;
}
