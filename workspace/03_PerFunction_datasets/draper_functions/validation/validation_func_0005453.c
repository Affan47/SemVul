unpack_comm(int n, int first, double *buf)
{
  int i,m,last;

  m = 0;
  last = first + n;
  for (i = first; i < last; i++)
    num_bonds[i] = static_cast<int> (buf[m++]);
}
