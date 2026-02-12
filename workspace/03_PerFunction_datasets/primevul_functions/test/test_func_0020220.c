operate_and_get_next (count, c)
     int count, c;
{
  int where;


  rl_newline (1, c);


  where = rl_explicit_arg ? count : where_history ();

  if (HISTORY_FULL () || (where >= history_length - 1) || rl_explicit_arg)
    saved_history_line_to_use = where;
  else
    saved_history_line_to_use = where + 1;

  old_rl_startup_hook = rl_startup_hook;
  rl_startup_hook = set_saved_history;

  return 0;
}
