perform_deferred_noexcept_checks (void)
{
  int i;
  pending_noexcept *p;
  location_t saved_loc = input_location;
  FOR_EACH_VEC_ELT (pending_noexcept, pending_noexcept_checks, i, p)
    {
      input_location = p->loc;
      maybe_noexcept_warning (p->fn);
    }
  input_location = saved_loc;
}
