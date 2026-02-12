execute_subshell_builtin_or_function (words, redirects, builtin, var,
				      pipe_in, pipe_out, async, fds_to_close,
				      flags)
     WORD_LIST *words;
     REDIRECT *redirects;
     sh_builtin_func_t *builtin;
     SHELL_VAR *var;
     int pipe_in, pipe_out, async;
     struct fd_bitmap *fds_to_close;
     int flags;
{
  int result, r, funcvalue;
#if defined (JOB_CONTROL)
  int jobs_hack;

  jobs_hack = (builtin == jobs_builtin) &&
		((subshell_environment & SUBSHELL_ASYNC) == 0 || pipe_out != NO_PIPE);
#endif


  login_shell = interactive = 0;

  if (async)
    subshell_environment |= SUBSHELL_ASYNC;
  if (pipe_in != NO_PIPE || pipe_out != NO_PIPE)
    subshell_environment |= SUBSHELL_PIPE;

  maybe_make_export_env ();

#if defined (JOB_CONTROL)


  if (jobs_hack)
    kill_current_pipeline ();
  else
    without_job_control ();

  set_sigchld_handler ();
#endif

  set_sigint_handler ();

  if (fds_to_close)
    close_fd_bitmap (fds_to_close);

  do_piping (pipe_in, pipe_out);

  if (do_redirections (redirects, RX_ACTIVE) != 0)
    exit (EXECUTION_FAILURE);

  if (builtin)
    {


      result = setjmp (top_level);


      funcvalue = 0;
      if (return_catch_flag && builtin == return_builtin)
        funcvalue = setjmp (return_catch);

      if (result == EXITPROG)
	exit (last_command_exit_value);
      else if (result)
	exit (EXECUTION_FAILURE);
      else if (funcvalue)
	exit (return_catch_value);
      else
	{
	  r = execute_builtin (builtin, words, flags, 1);
	  fflush (stdout);
	  if (r == EX_USAGE)
	    r = EX_BADUSAGE;
	  exit (r);
	}
    }
  else
    {
      r = execute_function (var, words, flags, fds_to_close, async, 1);
      fflush (stdout);
      exit (r);
    }
}
