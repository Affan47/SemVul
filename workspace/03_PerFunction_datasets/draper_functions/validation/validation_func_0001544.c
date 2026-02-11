factorial(int n)
{
  long unsigned f, x;
  int i;
  f = 1;
  for (i = 1; i <= n; i++) {
    x = f * i;
    if (x == ULONG_MAX || x < f)
      return 0;
    f = x;
  }
  return f;
}
