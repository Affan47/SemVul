execute_disk_command (words, redirects, command_line, pipe_in, pipe_out,
		      async, fds_to_close, cmdflags)
     WORD_LIST *words;
     REDIRECT *redirects;
     char *command_line;
     int pipe_in, pipe_out, async;
     struct fd_bitmap *fds_to_close;
     int cmdflags;
{
  char *pathname, *command, **args;
  int nofork, result;
  pid_t pid;
  SHELL_VAR *hookf;
  WORD_LIST *wl;

  nofork = (cmdflags & CMD_NO_FORK);
  pathname = words->word->word;

  result = EXECUTION_SUCCESS;
#if defined (RESTRICTED_SHELL)
  command = (char *)NULL;
  if (restricted && mbschr (pathname, '/'))
    {
      internal_error (_("%s: restricted: cannot specify `/' in command names"),
		    pathname);
      result = last_command_exit_value = EXECUTION_FAILURE;


      if (nofork && pipe_in == NO_PIPE && pipe_out == NO_PIPE)
	exit (last_command_exit_value);
      else
	goto parent_return;
    }
#endif

  command = search_for_command (pathname, 1);

  if (command)
    {
      maybe_make_export_env ();
      put_command_name_into_env (command);
    }


  if (nofork && pipe_in == NO_PIPE && pipe_out == NO_PIPE)
    pid = 0;
  else
    pid = make_child (savestring (command_line), async);

  if (pid == 0)
    {
      int old_interactive;

#if 0

#if !defined (ARG_MAX) || ARG_MAX >= 10240
      if (posixly_correct == 0)
	put_gnu_argv_flags_into_env ((long)getpid (), glob_argv_flags);
#endif
#endif

      reset_terminating_signals ();

      restore_original_signals ();


      if (async)
	{
	  if ((cmdflags & CMD_STDIN_REDIR) &&
		pipe_in == NO_PIPE &&
		(stdin_redirects (redirects) == 0))
	    async_redirect_stdin ();
	  setup_async_signals ();
	}


      if (fds_to_close)
	close_fd_bitmap (fds_to_close);

      do_piping (pipe_in, pipe_out);

      old_interactive = interactive;
      if (async)
	interactive = 0;

      subshell_environment = SUBSHELL_FORK;

      if (redirects && (do_redirections (redirects, RX_ACTIVE) != 0))
	{
#if defined (PROCESS_SUBSTITUTION)


	  unlink_fifo_list ();
#endif
	  exit (EXECUTION_FAILURE);
	}

      if (async)
	interactive = old_interactive;

      if (command == 0)
	{
	  hookf = find_function (NOTFOUND_HOOK);
	  if (hookf == 0)
	    {

	      if (ansic_shouldquote (pathname))
		pathname = ansic_quote (pathname, 0, NULL);
	      internal_error (_("%s: command not found"), pathname);
	      exit (EX_NOTFOUND);
	    }

	  wl = make_word_list (make_word (NOTFOUND_HOOK), words);
	  exit (execute_shell_function (hookf, wl));
	}


      args = strvec_from_word_list (words, 0, 0, (int *)NULL);
      exit (shell_execve (command, args, export_env));
    }
  else
    {
parent_return:
      QUIT;


      close_pipes (pipe_in, pipe_out);
#if defined (PROCESS_SUBSTITUTION) && defined (HAVE_DEV_FD)
      if (variable_context == 0)
        unlink_fifo_list ();
#endif
      FREE (command);
      return (result);
    }
}
