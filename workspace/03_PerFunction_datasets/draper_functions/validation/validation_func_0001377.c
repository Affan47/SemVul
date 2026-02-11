pack_data(double **buf)
{
  int nlocal = atom->nlocal;
  for (int i = 0; i < nlocal; i++) {
    buf[i][0] = tag[i];
    buf[i][1] = molecule[i];
    buf[i][2] = type[i];
    if (line[i] < 0) buf[i][3] = 0;
    else buf[i][3] = 1;
    if (line[i] < 0) buf[i][4] = rmass[i];
    else buf[i][4] = rmass[i]/bonus[line[i]].length;
    buf[i][5] = x[i][0];
    buf[i][6] = x[i][1];
    buf[i][7] = x[i][2];
    buf[i][8] = (image[i] & IMGMASK) - IMGMAX;
    buf[i][9] = (image[i] >> IMGBITS & IMGMASK) - IMGMAX;
    buf[i][10] = (image[i] >> IMG2BITS) - IMGMAX;
  }
}
