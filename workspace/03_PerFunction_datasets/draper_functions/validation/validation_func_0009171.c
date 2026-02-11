annotate_mm(ESL_MSA *msa, P7_HMM * hmm, const int *matuse, const int *matmap)
{
  int apos, k;
  int status;

  if (hmm->mm == NULL) return eslOK;

  ESL_ALLOC(msa->mm, sizeof(char) * (msa->alen+1));
  for (apos = 0; apos < msa->alen; apos++)
    msa->mm[apos] = '.';
  msa->mm[msa->alen] = '\0';

  for (k = 0; k < hmm->M; k++)
    if (matuse[k])
      msa->mm[matmap[k]-1] = hmm->mm[k];
  return eslOK;

 ERROR:
  return status;
}
