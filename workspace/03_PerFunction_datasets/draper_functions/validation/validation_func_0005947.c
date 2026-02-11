gt_str_array_get_str(const GtStrArray *sa, unsigned long strnum)
{
  gt_assert(sa && strnum < gt_array_size(sa->strings));
  return *(GtStr**) gt_array_get(sa->strings, strnum);
}
