compute_scalar()
{
  invoked_scalar = update->ntimestep;

  double **v = atom->v;
  double *ervel = atom->ervel;
  double *mass = atom->mass;
  int *spin = atom->spin;
  int *type = atom->type;
  int *mask = atom->mask;
  int nlocal = atom->nlocal;
  double mefactor = domain->dimension/4.0;

  double t = 0.0;

  if (mass) {
    for (int i = 0; i < nlocal; i++) {
      if (mask[i] & groupbit) {
        t += (v[i][0]*v[i][0] + v[i][1]*v[i][1] + v[i][2]*v[i][2]) *
          mass[type[i]];
        if (fabs(spin[i])==1) t += mefactor*mass[type[i]]*ervel[i]*ervel[i];
      }
    }
  }

  MPI_Allreduce(&t,&scalar,1,MPI_DOUBLE,MPI_SUM,world);
  if (dynamic) dof_compute();
  scalar *= tfactor;
  return scalar;
}
