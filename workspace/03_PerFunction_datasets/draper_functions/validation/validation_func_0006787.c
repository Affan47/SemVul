write_data(int n, double *mybuf)
{


  int m = 0;
  int k = 3*ntotal;
  for (int i = 0; i < n; i++) {
    coords[k++] = mybuf[m++];
    coords[k++] = mybuf[m++];
    coords[k++] = mybuf[m++];
    ntotal++;
  }


  if (ntotal == natoms) {
    write_frame();
    ntotal = 0;
  }
}
