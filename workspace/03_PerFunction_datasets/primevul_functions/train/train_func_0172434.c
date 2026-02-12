static char_u *option_expand(int opt_idx, char_u *val)
{

  if (!(options[opt_idx].flags & P_EXPAND) || options[opt_idx].var == NULL)
    return NULL;

  if (val == NULL) {
    val = *(char_u **)options[opt_idx].var;
  }


  if (val == NULL || STRLEN(val) > MAXPATHL) {
    return NULL;
  }


  expand_env_esc(val, NameBuff, MAXPATHL,
      (char_u **)options[opt_idx].var == &p_tags, FALSE,
      (char_u **)options[opt_idx].var == &p_sps ? (char_u *)"file:" :
      NULL);
  if (STRCMP(NameBuff, val) == 0)
    return NULL;

  return NameBuff;
}
