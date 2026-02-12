execute_simple_command (simple_command, pipe_in, pipe_out, async, fds_to_close)
     SIMPLE_COM *simple_command;
     int pipe_in, pipe_out, async;
     struct fd_bitmap *fds_to_close;
{
  WORD_LIST *words, *lastword;
  char *command_line, *lastarg, *temp;
  int first_word_quoted, result, builtin_is_special, already_forked, dofork;
  pid_t old_last_async_pid;
  sh_builtin_func_t *builtin;
  SHELL_VAR *func;
  volatile int old_builtin, old_command_builtin;

  result = EXECUTION_SUCCESS;
  special_builtin_failed = builtin_is_special = 0;
  command_line = (char *)0;

  QUIT;


  if (variable_context && interactive_shell && sourcelevel == 0)
    line_number -= function_line_number;


  command_string_index = 0;
  print_simple_command (simple_command);

#if 0
  if (signal_in_progress (DEBUG_TRAP) == 0 && (this_command_name == 0 || (STREQ (this_command_name, "trap") == 0)))
#else
  if (signal_in_progress (DEBUG_TRAP) == 0 && running_trap == 0)
#endif
    {
      FREE (the_printed_command_except_trap);
      the_printed_command_except_trap = the_printed_command ? savestring (the_printed_command) : (char *)0;
    }


  result = run_debug_trap ();
#if defined (DEBUGGER)


  if (debugging_mode && result != EXECUTION_SUCCESS)
    return (EXECUTION_SUCCESS);
#endif

  first_word_quoted =
    simple_command->words ? (simple_command->words->word->flags & W_QUOTED) : 0;

  last_command_subst_pid = NO_PID;
  old_last_async_pid = last_asynchronous_pid;

  already_forked = dofork = 0;


  dofork = pipe_in != NO_PIPE || pipe_out != NO_PIPE || async;


  if (dofork && pipe_in == NO_PIPE && pipe_out == NO_PIPE &&
	simple_command->words && simple_command->words->word &&
	simple_command->words->word->word &&
	(simple_command->words->word->word[0] == '%'))
    dofork = 0;

  if (dofork)
    {


      maybe_make_export_env ();


      if (make_child (savestring (the_printed_command_except_trap), async) == 0)
	{
	  already_forked = 1;
	  simple_command->flags |= CMD_NO_FORK;

	  subshell_environment = SUBSHELL_FORK;
	  if (pipe_in != NO_PIPE || pipe_out != NO_PIPE)
	    subshell_environment |= SUBSHELL_PIPE;
	  if (async)
	    subshell_environment |= SUBSHELL_ASYNC;


	  if (fds_to_close)
	    close_fd_bitmap (fds_to_close);

	  do_piping (pipe_in, pipe_out);
	  pipe_in = pipe_out = NO_PIPE;
#if defined (COPROCESS_SUPPORT)
	  coproc_closeall ();
#endif

	  last_asynchronous_pid = old_last_async_pid;
	}
      else
	{


	  if (pipe_out != NO_PIPE)
	    result = last_command_exit_value;
	  close_pipes (pipe_in, pipe_out);
#if defined (PROCESS_SUBSTITUTION) && defined (HAVE_DEV_FD)
	  unlink_fifo_list ();
#endif
	  command_line = (char *)NULL;
	  bind_lastarg ((char *)NULL);
	  return (result);
	}
    }


  if ((simple_command->flags & CMD_INHIBIT_EXPANSION) == 0)
    {
      current_fds_to_close = fds_to_close;
      fix_assignment_words (simple_command->words);

      if (simple_command->flags & CMD_IGNORE_RETURN)
	comsub_ignore_return++;
      words = expand_words (simple_command->words);
      if (simple_command->flags & CMD_IGNORE_RETURN)
	comsub_ignore_return--;
      current_fds_to_close = (struct fd_bitmap *)NULL;
    }
  else
    words = copy_word_list (simple_command->words);


  if (words == 0)
    {
      this_command_name = 0;
      result = execute_null_command (simple_command->redirects,
				     pipe_in, pipe_out,
				     already_forked ? 0 : async);
      if (already_forked)
	exit (result);
      else
	{
	  bind_lastarg ((char *)NULL);
	  set_pipestatus_from_exit (result);
	  return (result);
	}
    }

  lastarg = (char *)NULL;

  begin_unwind_frame ("simple-command");

  if (echo_command_at_execute)
    xtrace_print_word_list (words, 1);

  builtin = (sh_builtin_func_t *)NULL;
  func = (SHELL_VAR *)NULL;
  if ((simple_command->flags & CMD_NO_FUNCTIONS) == 0)
    {


      if (posixly_correct)
	{
	  builtin = find_special_builtin (words->word->word);
	  if (builtin)
	    builtin_is_special = 1;
	}
      if (builtin == 0)
	func = find_function (words->word->word);
    }


  if (builtin_is_special && interactive_shell == 0 && tempenv_assign_error)
    {
      last_command_exit_value = EXECUTION_FAILURE;
      jump_to_top_level (ERREXIT);
    }

  add_unwind_protect (dispose_words, words);
  QUIT;


  for (lastword = words; lastword->next; lastword = lastword->next)
    ;
  lastarg = lastword->word->word;

#if defined (JOB_CONTROL)

  if (words->word->word[0] == '%' && already_forked == 0)
    {
      this_command_name = async ? "bg" : "fg";
      last_shell_builtin = this_shell_builtin;
      this_shell_builtin = builtin_address (this_command_name);
      result = (*this_shell_builtin) (words);
      goto return_result;
    }


  if (job_control && already_forked == 0 && async == 0 &&
	!first_word_quoted &&
	!words->next &&
	words->word->word[0] &&
	!simple_command->redirects &&
	pipe_in == NO_PIPE &&
	pipe_out == NO_PIPE &&
	(temp = get_string_value ("auto_resume")))
    {
      int job, jflags, started_status;

      jflags = JM_STOPPED|JM_FIRSTMATCH;
      if (STREQ (temp, "exact"))
	jflags |= JM_EXACT;
      else if (STREQ (temp, "substring"))
	jflags |= JM_SUBSTRING;
      else
	jflags |= JM_PREFIX;
      job = get_job_by_name (words->word->word, jflags);
      if (job != NO_JOB)
	{
	  run_unwind_frame ("simple-command");
	  this_command_name = "fg";
	  last_shell_builtin = this_shell_builtin;
	  this_shell_builtin = builtin_address ("fg");

	  started_status = start_job (job, 1);
	  return ((started_status < 0) ? EXECUTION_FAILURE : started_status);
	}
    }
#endif

run_builtin:

  this_command_name = words->word->word;

  QUIT;


  if (func == 0 && builtin == 0)
    builtin = find_shell_builtin (this_command_name);

  last_shell_builtin = this_shell_builtin;
  this_shell_builtin = builtin;

  if (builtin || func)
    {
      if (builtin)
        {
	  old_builtin = executing_builtin;
	  old_command_builtin = executing_command_builtin;
	  unwind_protect_int (executing_builtin);
	  unwind_protect_int (executing_command_builtin);
        }
      if (already_forked)
	{


	  reset_signal_handlers ();
	  subshell_environment |= SUBSHELL_RESETTRAP;

	  if (async)
	    {
	      if ((simple_command->flags & CMD_STDIN_REDIR) &&
		    pipe_in == NO_PIPE &&
		    (stdin_redirects (simple_command->redirects) == 0))
		async_redirect_stdin ();
	      setup_async_signals ();
	    }

	  subshell_level++;
	  execute_subshell_builtin_or_function
	    (words, simple_command->redirects, builtin, func,
	     pipe_in, pipe_out, async, fds_to_close,
	     simple_command->flags);
	  subshell_level--;
	}
      else
	{
	  result = execute_builtin_or_function
	    (words, builtin, func, simple_command->redirects, fds_to_close,
	     simple_command->flags);
	  if (builtin)
	    {
	      if (result > EX_SHERRBASE)
		{
		  result = builtin_status (result);
		  if (builtin_is_special)
		    special_builtin_failed = 1;
		}


	      if (posixly_correct && builtin_is_special && temporary_env)
		merge_temporary_env ();
	    }
	  else
	    {
	      if (result == EX_USAGE)
		result = EX_BADUSAGE;
	      else if (result > EX_SHERRBASE)
		result = EXECUTION_FAILURE;
	    }

	  set_pipestatus_from_exit (result);

	  goto return_result;
	}
    }

  if (autocd && interactive && words->word && is_dirname (words->word->word))
    {
      words = make_word_list (make_word ("cd"), words);
      xtrace_print_word_list (words, 0);
      goto run_builtin;
    }

  if (command_line == 0)
    command_line = savestring (the_printed_command_except_trap);

#if defined (PROCESS_SUBSTITUTION)
  if ((subshell_environment & SUBSHELL_COMSUB) && (simple_command->flags & CMD_NO_FORK) && fifos_pending() > 0)
    simple_command->flags &= ~CMD_NO_FORK;
#endif

  result = execute_disk_command (words, simple_command->redirects, command_line,
			pipe_in, pipe_out, async, fds_to_close,
			simple_command->flags);

 return_result:
  bind_lastarg (lastarg);
  FREE (command_line);
  dispose_words (words);
  if (builtin)
    {
      executing_builtin = old_builtin;
      executing_command_builtin = old_command_builtin;
    }
  discard_unwind_frame ("simple-command");
  this_command_name = (char *)NULL;
  return (result);
}
