resize(int nsz)
{
  if (nsz != sz)
  {
    float *nd = 0;
    if (nsz > 0)
    {
      nd = new float[nsz];
      for (int i=0; i<nsz && i<sz; i++)
        nd[i] = d[i];
    }
    long delta = (nsz - sz) * sizeof(float);
    sz = nsz;
    delete [] d;
    d = nd;
    return delta;
  }
  return 0;
}
