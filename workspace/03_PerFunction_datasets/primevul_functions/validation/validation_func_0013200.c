execute_in_subshell (command, asynchronous, pipe_in, pipe_out, fds_to_close)
     COMMAND *command;
     int asynchronous;
     int pipe_in, pipe_out;
     struct fd_bitmap *fds_to_close;
{
  int user_subshell, return_code, function_value, should_redir_stdin, invert;
  int ois, user_coproc;
  int result;
  volatile COMMAND *tcom;

  USE_VAR(user_subshell);
  USE_VAR(user_coproc);
  USE_VAR(invert);
  USE_VAR(tcom);
  USE_VAR(asynchronous);

  subshell_level++;
  should_redir_stdin = (asynchronous && (command->flags & CMD_STDIN_REDIR) &&
			  pipe_in == NO_PIPE &&
			  stdin_redirects (command->redirects) == 0);

  invert = (command->flags & CMD_INVERT_RETURN) != 0;
  user_subshell = command->type == cm_subshell || ((command->flags & CMD_WANT_SUBSHELL) != 0);
  user_coproc = command->type == cm_coproc;

  command->flags &= ~(CMD_FORCE_SUBSHELL | CMD_WANT_SUBSHELL | CMD_INVERT_RETURN);


  if (asynchronous)
    {
#if defined (JOB_CONTROL)


      original_pgrp = -1;
#endif
      ois = interactive_shell;
      interactive_shell = 0;


      if (ois != interactive_shell)
	expand_aliases = 0;
    }


  login_shell = interactive = 0;

  if (user_subshell)
    subshell_environment = SUBSHELL_PAREN;
  else
    {
      subshell_environment = 0;
      if (asynchronous)
	subshell_environment |= SUBSHELL_ASYNC;
      if (pipe_in != NO_PIPE || pipe_out != NO_PIPE)
	subshell_environment |= SUBSHELL_PIPE;
      if (user_coproc)
	subshell_environment |= SUBSHELL_COPROC;
    }

  reset_terminating_signals ();


  reset_signal_handlers ();
  subshell_environment |= SUBSHELL_RESETTRAP;


  if (asynchronous)
    {
      setup_async_signals ();
      asynchronous = 0;
    }

#if defined (JOB_CONTROL)
  set_sigchld_handler ();
#endif

  set_sigint_handler ();

#if defined (JOB_CONTROL)


  without_job_control ();
#endif

  if (fds_to_close)
    close_fd_bitmap (fds_to_close);

  do_piping (pipe_in, pipe_out);

#if defined (COPROCESS_SUPPORT)
  coproc_closeall ();
#endif


  if (user_subshell)
    {
      stdin_redir = stdin_redirects (command->redirects);
      restore_default_signal (0);
    }


  if (should_redir_stdin && stdin_redir == 0)
    async_redirect_stdin ();


  if (command->redirects)
    {
      if (do_redirections (command->redirects, RX_ACTIVE) != 0)
	exit (invert ? EXECUTION_SUCCESS : EXECUTION_FAILURE);

      dispose_redirects (command->redirects);
      command->redirects = (REDIRECT *)NULL;
    }

  if (command->type == cm_subshell)
    tcom = command->value.Subshell->command;
  else if (user_coproc)
    tcom = command->value.Coproc->command;
  else
    tcom = command;

  if (command->flags & CMD_TIME_PIPELINE)
    tcom->flags |= CMD_TIME_PIPELINE;
  if (command->flags & CMD_TIME_POSIX)
    tcom->flags |= CMD_TIME_POSIX;


  if ((command->flags & CMD_IGNORE_RETURN) && tcom != command)
    tcom->flags |= CMD_IGNORE_RETURN;


  if ((user_subshell || user_coproc) && (tcom->type == cm_simple || tcom->type == cm_subshell) &&
      ((tcom->flags & CMD_TIME_PIPELINE) == 0) &&
      ((tcom->flags & CMD_INVERT_RETURN) == 0))
    {
      tcom->flags |= CMD_NO_FORK;
      if (tcom->type == cm_simple)
	tcom->value.Simple->flags |= CMD_NO_FORK;
    }

  invert = (tcom->flags & CMD_INVERT_RETURN) != 0;
  tcom->flags &= ~CMD_INVERT_RETURN;

  result = setjmp (top_level);


  function_value = 0;
  if (return_catch_flag)
    function_value = setjmp (return_catch);


  if (result == EXITPROG)
    invert = 0, return_code = last_command_exit_value;
  else if (result)
    return_code = EXECUTION_FAILURE;
  else if (function_value)
    return_code = return_catch_value;
  else
    return_code = execute_command_internal ((COMMAND *)tcom, asynchronous, NO_PIPE, NO_PIPE, fds_to_close);


  if (invert)
    return_code = (return_code == EXECUTION_SUCCESS) ? EXECUTION_FAILURE
						     : EXECUTION_SUCCESS;


  if (user_subshell && signal_is_trapped (0))
    {
      last_command_exit_value = return_code;
      return_code = run_exit_trap ();
    }

  subshell_level--;
  return (return_code);

}
