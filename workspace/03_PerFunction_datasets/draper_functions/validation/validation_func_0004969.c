Fd_Unify_With_Integer0(WamWord *fdv_adr, int n)
{

  Fd_Before_Add_Cstr();

  return Fd_Tell_Value(fdv_adr, n) && Fd_After_Add_Cstr();
}
