gimple_stmt_nonnegative_warnv_p (gimple stmt, bool *strict_overflow_p)
{
  switch (gimple_code (stmt))
    {
    case GIMPLE_ASSIGN:
      return gimple_assign_nonnegative_warnv_p (stmt, strict_overflow_p);
    case GIMPLE_CALL:
      return gimple_call_nonnegative_warnv_p (stmt, strict_overflow_p);
    default:
      gcc_unreachable ();
    }
}
