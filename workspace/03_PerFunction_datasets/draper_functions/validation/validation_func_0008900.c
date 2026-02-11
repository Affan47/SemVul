homogonize_inserts(P7_HMM *hmm)
{
  int i;
  float tii = 0.0;
  float tmi = 0.0;
  float dmi;
  float tm_md;


  for (i=1; i<hmm->M; i++ ) {
    tii += hmm->t[i][p7H_II];
    tmi += hmm->t[i][p7H_MI];
  }


  tii /= (hmm->M-1);
  tmi /= (hmm->M-1);


  for (i=1; i<hmm->M; i++ ) {

    hmm->t[i][p7H_II]  = tii;
    hmm->t[i][p7H_IM]  = tmi;

    dmi = tmi - hmm->t[i][p7H_MI];
    hmm->t[i][p7H_MI]  = tmi;


    tm_md = hmm->t[i][p7H_MM] + hmm->t[i][p7H_MD];
    hmm->t[i][p7H_MM] -= (tm_md == 0 ? 0 : (dmi * hmm->t[i][p7H_MM]/tm_md)) ;
    hmm->t[i][p7H_MD] -= (tm_md == 0 ? 0 : (dmi * hmm->t[i][p7H_MD]/tm_md)) ;

  }

  return eslOK;
}
