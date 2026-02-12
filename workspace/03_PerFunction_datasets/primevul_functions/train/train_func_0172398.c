void ExpandOldSetting(int *num_file, char_u ***file)
{
  char_u *var = NULL;

  *num_file = 0;
  *file = (char_u **)xmalloc(sizeof(char_u *));


  if (expand_option_idx < 0) {
    expand_option_idx = findoption(expand_option_name);
  }

  if (expand_option_idx >= 0) {

    option_value2string(&options[expand_option_idx], expand_option_flags);
    var = NameBuff;
  } else if (var == NULL)
    var = (char_u *)"";


  char_u *buf = vim_strsave_escaped(var, escape_chars);

#ifdef BACKSLASH_IN_FILENAME


  for (var = buf; *var != NUL; mb_ptr_adv(var))
    if (var[0] == '\\' && var[1] == '\\'
        && expand_option_idx >= 0
        && (options[expand_option_idx].flags & P_EXPAND)
        && vim_isfilec(var[2])
        && (var[2] != '\\' || (var == buf && var[4] != '\\')))
      STRMOVE(var, var + 1);
#endif

  *file[0] = buf;
  *num_file = 1;
}
