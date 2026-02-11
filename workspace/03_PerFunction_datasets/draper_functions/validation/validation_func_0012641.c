double_int_rrotate (double_int a, HOST_WIDE_INT count, unsigned int prec)
{
  double_int t1, t2;

  count %= prec;
  if (count < 0)
    count += prec;

  t1 = double_int_rshift (a, count, prec, false);
  t2 = double_int_lshift (a, prec - count, prec, false);

  return double_int_ior (t1, t2);
}
