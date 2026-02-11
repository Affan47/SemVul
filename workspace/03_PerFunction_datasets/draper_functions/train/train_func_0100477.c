gt_countingsort_unit_test(GtError *err)
{
  unsigned int numbers[]        = { 1, 2, 1, 2, 0 }, numbers_out[5],
               sorted_numbers[] = { 0, 1, 1, 2, 2 };
  int had_err = 0;
  gt_error_check(err);
  gt_countingsort(numbers_out, numbers, sizeof (unsigned int), 5,
                  gt_countingsort_get_max(numbers, sizeof (unsigned int), 5,
                                          NULL, get_int),
                  NULL,  get_int);
  gt_ensure(had_err,
         !memcmp(sorted_numbers, numbers_out, sizeof (unsigned int) * 5));
  return had_err;
}
