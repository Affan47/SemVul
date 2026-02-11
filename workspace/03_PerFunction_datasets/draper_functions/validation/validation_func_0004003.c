p7_spensemble_GetClusterCoords(P7_SPENSEMBLE *sp, int which, int *opt_i, int *opt_j, int *opt_k, int *opt_m, float *opt_p)
{
  if (opt_i != NULL) *opt_i = sp->sigc[which].i;
  if (opt_j != NULL) *opt_j = sp->sigc[which].j;
  if (opt_k != NULL) *opt_k = sp->sigc[which].k;
  if (opt_m != NULL) *opt_m = sp->sigc[which].m;
  if (opt_p != NULL) *opt_p = sp->sigc[which].prob;
  return eslOK;
}
