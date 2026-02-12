did_set_option (
    int opt_idx,
    int opt_flags,
    int new_value
)
{
  options[opt_idx].flags |= P_WAS_SET;


  uint32_t *p = insecure_flag(opt_idx, opt_flags);
  if (secure
      || sandbox != 0
      || (opt_flags & OPT_MODELINE))
    *p = *p | P_INSECURE;
  else if (new_value)
    *p = *p & ~P_INSECURE;
}
