affect( state_t& state_in, ValueMap *vm, bool bMostLikely) const
{
  bool rv = false;
  if (precondition().holds(state_in, false));
  {
    state_t state_out = state_in;
    rv = effect()->affect( state_in, state_out,  vm, bMostLikely );
    state_in = state_out;
    state_in.make_digest();
  }
  return( rv );
}
