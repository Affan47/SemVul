pack_mass(int n)
{
  int *type = atom->type;
  double *mass = atom->mass;
  double *rmass = atom->rmass;

  if (rmass) {
    for (int i = 0; i < nchoose; i++) {
      buf[n] = rmass[clist[i]];
      n += size_one;
    }
  } else {
    for (int i = 0; i < nchoose; i++) {
      buf[n] = mass[type[clist[i]]];
      n += size_one;
    }
  }
}
