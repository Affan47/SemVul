dof(int igroup)
{
  int groupbit = group->bitmask[igroup];


  int *mask = atom->mask;
  int nlocal = atom->nlocal;

  int *ncount = new int[nbody];
  for (int ibody = 0; ibody < nbody; ibody++) ncount[ibody] = 0;

  for (int i = 0; i < nlocal; i++)
    if (body[i] >= 0 && mask[i] & groupbit) ncount[body[i]]++;

  int *nall = new int[nbody];
  MPI_Allreduce(ncount,nall,nbody,MPI_INT,MPI_SUM,world);


  int n = 0;
  for (int ibody = 0; ibody < nbody; ibody++) {
    if (nall[ibody] > 2) n += 3*nall[ibody] - 6;
    else if (nall[ibody] == 2) n++;
  }

  delete [] ncount;
  delete [] nall;

  return n;
}
