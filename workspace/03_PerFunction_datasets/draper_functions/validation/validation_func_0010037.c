p7_ParameterEstimation(P7_HMM *hmm, const P7_PRIOR *pri)
{
  int   k;
  double c[p7_MAXABET];
  double p[p7_MAXABET];
  double mix[p7_MAXDCHLET];


  if (pri==NULL) return p7_hmm_Renormalize(hmm);


  for (k = 0; k <= hmm->M; k++) {
    esl_vec_F2D(hmm->t[k], 3, c);
    esl_mixdchlet_MPParameters(c, 3, pri->tm, mix, p);
    esl_vec_D2F(p, 3, hmm->t[k]);
  }
  hmm->t[hmm->M][p7H_MD] = 0.0;
  esl_vec_FNorm(hmm->t[hmm->M], 3);


  for (k = 0; k <= hmm->M; k++) {
    esl_vec_F2D(hmm->t[k]+3, 2, c);
    esl_mixdchlet_MPParameters(c, 2, pri->ti, mix, p);
    esl_vec_D2F(p, 2, hmm->t[k]+3);
  }


  for (k = 1; k < hmm->M; k++) {
    esl_vec_F2D(hmm->t[k]+5, 2, c);
    esl_mixdchlet_MPParameters(c, 2, pri->td, mix, p);
    esl_vec_D2F(p, 2, hmm->t[k]+5);
  }
  hmm->t[0][p7H_DM] = hmm->t[hmm->M][p7H_DM] = 1.0;
  hmm->t[0][p7H_DD] = hmm->t[hmm->M][p7H_DD] = 0.0;


  for (k = 1; k <= hmm->M; k++) {
    esl_vec_F2D(hmm->mat[k], hmm->abc->K, c);
    esl_mixdchlet_MPParameters(c, hmm->abc->K, pri->em, mix, p);
    esl_vec_D2F(p, hmm->abc->K, hmm->mat[k]);
  }
  esl_vec_FSet(hmm->mat[0], hmm->abc->K, 0.);
  hmm->mat[0][0] = 1.0;


  for (k = 0; k <= hmm->M; k++) {
    esl_vec_F2D(hmm->ins[k], hmm->abc->K, c);
    esl_mixdchlet_MPParameters(c, hmm->abc->K, pri->ei, mix, p);
    esl_vec_D2F(p, hmm->abc->K, hmm->ins[k]);
  }
  return eslOK;
}
