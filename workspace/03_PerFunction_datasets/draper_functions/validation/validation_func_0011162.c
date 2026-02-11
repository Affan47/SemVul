initialize_info_session (NODE *node, int clear_screen)
{
  char *term_name = getenv ("TERM");
  terminal_initialize_terminal (term_name);

  if (terminal_is_dumb_p)
    {
      if (!term_name)
        term_name = "dumb";

      info_error (msg_term_too_dumb, term_name);
      exit (EXIT_FAILURE);
    }

  if (clear_screen)
    {
      terminal_prep_terminal ();
      terminal_clear_screen ();
    }

  initialize_info_keymaps ();
  window_initialize_windows (screenwidth, screenheight);
  initialize_info_signal_handler ();
  display_initialize_display (screenwidth, screenheight);
  info_set_node_of_window (0, active_window, node);


  window_deletion_notifier = (VFunction *) forget_window_and_nodes;


  if (!info_input_stream)
    {
      setbuf (stdin, NULL);
      info_input_stream = stdin;
    }

  info_windows_initialized_p = 1;
}
