cmp(const void *a_ptr, const void *b_ptr, GT_UNUSED void *unused)
{
  int a, b;
  gt_assert(a_ptr && b_ptr);
  a = *(int*) a_ptr;
  b = *(int*) b_ptr;
  if (a == b)
    return 0;
  if (a < b)
    return -1;
  return 1;
}
