_nrrd_TMF_d2_c2_2ef_N_d(double *f, const double *x, size_t len, const double *parm) {
  double t;
  size_t I;
  int i;

  AIR_UNUSED(parm);
  for (I=0; I<len; I++) {
    t = x[I] + 3;
    i = (int)((t<0) ? t-1 : t);
    t -= i;
    f[I] = TMF_d2_c2_2ef(parm[0], i, t);
  }
}
