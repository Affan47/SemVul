gimple_indirect_call_to_profile (gimple stmt, histogram_values *values)
{
  tree callee;

  if (gimple_code (stmt) != GIMPLE_CALL
      || gimple_call_internal_p (stmt)
      || gimple_call_fndecl (stmt) != NULL_TREE)
    return;

  callee = gimple_call_fn (stmt);

  values->reserve (3);

  values->quick_push (gimple_alloc_histogram_value (cfun, HIST_TYPE_INDIR_CALL,
						    stmt, callee));

  return;
}
