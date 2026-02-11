last_error(void) const
{
  if (last_retval_rep.type == eci_return_value::retval_error)
    return last_retval_rep.string_val;

  return string();
}
