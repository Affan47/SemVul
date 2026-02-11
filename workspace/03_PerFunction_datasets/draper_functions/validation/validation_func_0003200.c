wdist (a_width l, a_width r)
{
  a_cost c = l > r ? l - r : r - l;
  return c * c;
}
