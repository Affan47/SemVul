set_bash_input ()
{


#if defined (BUFFERED_INPUT)
  if (interactive == 0)
    sh_unset_nodelay_mode (default_buffered_input);
  else
#endif
    sh_unset_nodelay_mode (fileno (stdin));


  if (interactive && no_line_editing == 0)
    with_input_from_stdin ();
#if defined (BUFFERED_INPUT)
  else if (interactive == 0)
    with_input_from_buffered_stream (default_buffered_input, dollar_vars[0]);
#endif
  else
    with_input_from_stream (default_input, dollar_vars[0]);
}
