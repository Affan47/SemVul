_nrrdDA41_d(double x, const double *parm) {
  double S;
  double A;
  int sgn = 1;

  S = parm[0]; A = parm[1];
  if (x < 0) { x = -x; sgn = -1; }
  x /= S;
  return sgn*_DAQUARTIC(x, A)/(S*S);
}
