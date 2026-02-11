retry_incomplete_types (void)
{
  int i;

  for (i = vec_safe_length (incomplete_types) - 1; i >= 0; i--)
    if (should_emit_struct_debug ((*incomplete_types)[i], DINFO_USAGE_DIR_USE))
      gen_type_die ((*incomplete_types)[i], comp_unit_die ());
}
