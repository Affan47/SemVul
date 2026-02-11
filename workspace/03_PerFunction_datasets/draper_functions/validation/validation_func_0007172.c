level_index(int n) const
{
  int sum = 0;
  int term = 1;
  while (n--) {
    sum += term;
    term *= branching_factor_;
  }
  return sum;
}
