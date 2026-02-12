set_string_option_direct (
    char_u *name,
    int opt_idx,
    char_u *val,
    int opt_flags,
    int set_sid
)
{
  char_u      *s;
  char_u      **varp;
  int both = (opt_flags & (OPT_LOCAL | OPT_GLOBAL)) == 0;
  int idx = opt_idx;

  if (idx == -1) {
    idx = findoption(name);
    if (idx < 0) {
      EMSG2(_(e_intern2), "set_string_option_direct()");
      EMSG2(_("For option %s"), name);
      return;
    }
  }

  if (options[idx].var == NULL)
    return;

  assert((void *) options[idx].var != (void *) &p_shada);

  s = vim_strsave(val);
  {
    varp = (char_u **)get_varp_scope(&(options[idx]),
        both ? OPT_LOCAL : opt_flags);
    if ((opt_flags & OPT_FREE) && (options[idx].flags & P_ALLOCED))
      free_string_option(*varp);
    *varp = s;


    if (both)
      set_string_option_global(idx, varp);

    options[idx].flags |= P_ALLOCED;


    if (((int)options[idx].indir & PV_BOTH) && both) {
      free_string_option(*varp);
      *varp = empty_option;
    }
    if (set_sid != SID_NONE)
      set_option_scriptID_idx(idx, opt_flags,
          set_sid == 0 ? current_SID : set_sid);
  }
}
