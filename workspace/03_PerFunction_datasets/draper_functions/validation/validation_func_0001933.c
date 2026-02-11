fp_const_from_val (REAL_VALUE_TYPE *r)
{
  int i;

  if (!fp_consts_inited)
    init_fp_table ();

  for (i = 0; i < 8; i++)
    if (REAL_VALUES_EQUAL (*r, values_fp[i]))
      return strings_fp[i];

  gcc_unreachable ();
}
