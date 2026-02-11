compute_nincluded (bool *includep, int nchromosomes) {
  int nincluded = 0, i;

  for (i = 0; i < nchromosomes; i++) {
    if (includep[i] == true) {
      nincluded++;
    }
  }
  return nincluded;
}
