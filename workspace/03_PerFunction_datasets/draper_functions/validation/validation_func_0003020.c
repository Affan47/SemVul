ovl_is_coverage_point(
  const expression* exp
) { PROFILE(OVL_IS_COVERAGE_POINT);

  bool retval = (exp->op == EXP_OP_TASK_CALL) && (strcmp( exp->name, "ovl_cover_t" ) == 0);

  PROFILE_END;

  return( retval );

}
