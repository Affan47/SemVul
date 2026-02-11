_commFailureExceptionHandler(void*& cookie)
{
  if (pd_flags.commfail_exception_handler) {
    omniExHandlers_iterator iter;
    omniExHandlers* hp = iter.find(this);
    if (hp != 0) {
      cookie = hp->commfail_cookie;
      void* result = hp->commfail_hdr;
      return result;
    }
  }
  return 0;
}
