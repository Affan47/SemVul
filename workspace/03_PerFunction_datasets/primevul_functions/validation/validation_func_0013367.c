sv_locale (name)
     char *name;
{
  char *v;
  int r;

  v = get_string_value (name);
  if (name[0] == 'L' && name[1] == 'A')
    r = set_lang (name, v);
  else
    r = set_locale_var (name, v);

#if 1
  if (r == 0 && posixly_correct)
    last_command_exit_value = 1;
#endif
}
