edit_and_execute_command (count, c, editing_mode, edit_command)
     int count, c, editing_mode;
     char *edit_command;
{
  char *command, *metaval;
  int r, rrs, metaflag;
  sh_parser_state_t ps;

  rrs = rl_readline_state;
  saved_command_line_count = current_command_line_count;


  rl_newline (1, c);

  if (rl_explicit_arg)
    {
      command = (char *)xmalloc (strlen (edit_command) + 8);
      sprintf (command, "%s %d", edit_command, count);
    }
  else
    {


      using_history ();
      current_command_line_count++;
      bash_add_history (rl_line_buffer);
      current_command_line_count = 0;
      bash_add_history ("");
      history_lines_this_session++;
      using_history ();
      command = savestring (edit_command);
    }

  metaval = rl_variable_value ("input-meta");
  metaflag = RL_BOOLEAN_VARIABLE_VALUE (metaval);

  if (rl_deprep_term_function)
    (*rl_deprep_term_function) ();
  save_parser_state (&ps);
  r = parse_and_execute (command, (editing_mode == VI_EDITING_MODE) ? "v" : "C-xC-e", SEVAL_NOHIST);
  restore_parser_state (&ps);
  if (rl_prep_term_function)
    (*rl_prep_term_function) (metaflag);

  current_command_line_count = saved_command_line_count;


  rl_line_buffer[0] = '\0';
  rl_point = rl_end = 0;
  rl_done = 0;
  rl_readline_state = rrs;

#if defined (VI_MODE)
  if (editing_mode == VI_EDITING_MODE)
    rl_vi_insertion_mode (1, c);
#endif

  rl_forced_update_display ();

  return r;
}
