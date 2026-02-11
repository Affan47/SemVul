operator<<=(from_string s)
{
  CORBA::TypeCode_ptr tc;

  if (s.bound)
    tc = CORBA::TypeCode::NP_string_tc(s.bound);
  else
    tc = CORBA::TypeCode::_duplicate(CORBA::_tc_string);

  PR_clearData();
  pd_tc = tc;

  if (s.nc) {
    PR_insert(tc, marshalString_fn, deleteString_fn, s.val);
  }
  else {
    char* ns = CORBA::string_dup(s.val);
    PR_insert(tc, marshalString_fn, deleteString_fn, ns);
  }
}
