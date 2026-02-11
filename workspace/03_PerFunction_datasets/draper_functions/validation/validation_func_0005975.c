_NP_duplicate() const
{

  Any* ex = new Any(*pd_exception);
  Exception* e = new UnknownUserException(ex);
  return e;
}
