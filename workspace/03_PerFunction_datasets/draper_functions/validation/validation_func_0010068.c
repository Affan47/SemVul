size(int n)
{
  if (patternflag == UNSET) error->all("Cannot size without pattern");
  sizestyle = SAME;

  nsize = n;

  nsendmax = 0;
  for (int i = 0; i < nsend+self; i++) {
    sendsize[i] = nsize * sendcount[i];
    if (i < nsend) nsendmax = MAX(nsendmax,sendsize[i]);
  }

  for (int i = 0; i < nrecv; i++) recvsize[i] = nsize * recvcount[i];
  nbytesrecv = nsize * ndatumrecv;

  return nbytesrecv;
}
