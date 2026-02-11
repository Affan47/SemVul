init_one(int i, int j)
{
  if (setflag[i][j] == 0) {
    error->all(FLERR,"for pair style coul/diel, parameters need to be set explicitly for all pairs.");
  }

  double *q = atom->q;
  double qqrd2e = force->qqrd2e;

  if (offset_flag) {
    double rarg = (cut[i][j]-rme[i][j])/sigmae[i][j];
    double epsr=a_eps+b_eps*tanh(rarg);
    offset[i][j] = qqrd2e*q[i]*q[j]*((eps_s/epsr) -1.)/cut[i][j];
  } else offset[i][j] = 0.0;


  sigmae[j][i] = sigmae[i][j];
  rme[j][i] = rme[i][j];
  offset[j][i] = offset[i][j];
  cut[j][i] = cut[i][j];

  return cut[i][j];
}
