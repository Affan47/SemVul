main (argc, argv, env)
     int argc;
     char **argv, **env;
#endif
{
  register int i;
  int code, old_errexit_flag;
#if defined (RESTRICTED_SHELL)
  int saverst;
#endif
  volatile int locally_skip_execution;
  volatile int arg_index, top_level_arg_index;
#ifdef __OPENNT
  char **env;

  env = environ;
#endif

  USE_VAR(argc);
  USE_VAR(argv);
  USE_VAR(env);
  USE_VAR(code);
  USE_VAR(old_errexit_flag);
#if defined (RESTRICTED_SHELL)
  USE_VAR(saverst);
#endif


  code = setjmp_nosigs (top_level);
  if (code)
    exit (2);

  xtrace_init ();

#if defined (USING_BASH_MALLOC) && defined (DEBUG) && !defined (DISABLE_MALLOC_WRAPPERS)
  malloc_set_register (1);
#endif

  check_dev_tty ();

#ifdef __CYGWIN__
  _cygwin32_check_tmp ();
#endif


  while (debugging_login_shell) sleep (3);

  set_default_locale ();

  running_setuid = uidget ();

  if (getenv ("POSIXLY_CORRECT") || getenv ("POSIX_PEDANTIC"))
    posixly_correct = 1;

#if defined (USE_GNU_MALLOC_LIBRARY)
  mcheck (programming_error, (void (*) ())0);
#endif

  if (setjmp_sigs (subshell_top_level))
    {
      argc = subshell_argc;
      argv = subshell_argv;
      env = subshell_envp;
      sourced_env = 0;
    }

  shell_reinitialized = 0;


  arg_index = 1;
  if (arg_index > argc)
    arg_index = argc;
  command_execution_string = shell_script_filename = (char *)NULL;
  want_pending_command = locally_skip_execution = read_from_stdin = 0;
  default_input = stdin;
#if defined (BUFFERED_INPUT)
  default_buffered_input = -1;
#endif


  login_shell = make_login_shell = 0;


  if (shell_initialized || shell_name)
    {

      if (*shell_name == '-')
	shell_name++;

      shell_reinitialize ();
      if (setjmp_nosigs (top_level))
	exit (2);
    }

  shell_environment = env;
  set_shell_name (argv[0]);
  shell_start_time = NOW;


  arg_index = parse_long_options (argv, arg_index, argc);

  if (want_initial_help)
    {
      show_shell_usage (stdout, 1);
      exit (EXECUTION_SUCCESS);
    }

  if (do_version)
    {
      show_shell_version (1);
      exit (EXECUTION_SUCCESS);
    }

  echo_input_at_read = verbose_flag;


  this_command_name = shell_name;
  arg_index = parse_shell_options (argv, arg_index, argc);


  if (make_login_shell)
    {
      login_shell++;
      login_shell = -login_shell;
    }

  set_login_shell ("login_shell", login_shell != 0);

  if (dump_po_strings)
    dump_translatable_strings = 1;

  if (dump_translatable_strings)
    read_but_dont_execute = 1;

  if (running_setuid && privileged_mode == 0)
    disable_priv_mode ();


  if (want_pending_command)
    {
      command_execution_string = argv[arg_index];
      if (command_execution_string == 0)
	{
	  report_error (_("%s: option requires an argument"), "-c");
	  exit (EX_BADUSAGE);
	}
      arg_index++;
    }
  this_command_name = (char *)NULL;


  if (forced_interactive ||
      (!command_execution_string &&
       wordexp_only == 0 &&
       ((arg_index == argc) ||
	read_from_stdin) &&
       isatty (fileno (stdin)) &&
       isatty (fileno (stderr))))
    init_interactive ();
  else
    init_noninteractive ();


  if (login_shell && interactive_shell)
    {
      for (i = 3; i < 20; i++)
	SET_CLOSE_ON_EXEC (i);
    }


  if (posixly_correct)
    {
      bind_variable ("POSIXLY_CORRECT", "y", 0);
      sv_strict_posix ("POSIXLY_CORRECT");
    }


  if (shopt_alist)
    run_shopt_alist ();


  shell_initialize ();

  set_default_lang ();
  set_default_locale_vars ();


  if (interactive_shell)
    {
      char *term, *emacs, *inside_emacs;
      int emacs_term, in_emacs;

      term = get_string_value ("TERM");
      emacs = get_string_value ("EMACS");
      inside_emacs = get_string_value ("INSIDE_EMACS");

      if (inside_emacs)
	{
	  emacs_term = strstr (inside_emacs, ",term:") != 0;
	  in_emacs = 1;
	}
      else if (emacs)
	{

	  emacs_term = strstr (emacs, " (term:") != 0;
	  in_emacs = emacs_term || STREQ (emacs, "t");
	}
      else
	in_emacs = emacs_term = 0;


      no_line_editing |= STREQ (term, "emacs");
      no_line_editing |= in_emacs && STREQ (term, "dumb");


      running_under_emacs = in_emacs || STREQN (term, "emacs", 5);
      running_under_emacs += emacs_term && STREQN (term, "eterm", 5);

      if (running_under_emacs)
	gnu_error_format = 1;
    }

  top_level_arg_index = arg_index;
  old_errexit_flag = exit_immediately_on_error;


  code = setjmp_sigs (top_level);
  if (code)
    {
      if (code == EXITPROG || code == ERREXIT)
	exit_shell (last_command_exit_value);
      else
	{
#if defined (JOB_CONTROL)

	  set_job_control (interactive_shell);
#endif


	  exit_immediately_on_error += old_errexit_flag;
	  locally_skip_execution++;
	}
    }

  arg_index = top_level_arg_index;


  if (interactive_shell == 0)
    {
      unbind_variable ("PS1");
      unbind_variable ("PS2");
      interactive = 0;
#if 0

      expand_aliases = posixly_correct;
#endif
    }
  else
    {
      change_flag ('i', FLAG_ON);
      interactive = 1;
    }

#if defined (RESTRICTED_SHELL)


  restricted_shell = shell_is_restricted (shell_name);


  saverst = restricted;
  restricted = 0;
#endif


  if (wordexp_only)
    ;
  else if (command_execution_string)
    arg_index = bind_args (argv, arg_index, argc, 0);
  else if (arg_index != argc && read_from_stdin == 0)
    {
      shell_script_filename = argv[arg_index++];
      arg_index = bind_args (argv, arg_index, argc, 1);
    }
  else
    arg_index = bind_args (argv, arg_index, argc, 1);


  if (locally_skip_execution == 0 && running_setuid == 0)
    {
      old_errexit_flag = exit_immediately_on_error;
      exit_immediately_on_error = 0;

      run_startup_files ();
      exit_immediately_on_error += old_errexit_flag;
    }


  if (act_like_sh)
    {
      bind_variable ("POSIXLY_CORRECT", "y", 0);
      sv_strict_posix ("POSIXLY_CORRECT");
    }

#if defined (RESTRICTED_SHELL)


  restricted = saverst || restricted;
  if (shell_reinitialized == 0)
    maybe_make_restricted (shell_name);
#endif

#if defined (WORDEXP_OPTION)
  if (wordexp_only)
    {
      startup_state = 3;
      last_command_exit_value = run_wordexp (argv[top_level_arg_index]);
      exit_shell (last_command_exit_value);
    }
#endif

  cmd_init ();
  uwp_init ();

  if (command_execution_string)
    {
      startup_state = 2;

      if (debugging_mode)
	start_debugger ();

#if defined (ONESHOT)
      executing = 1;
      run_one_command (command_execution_string);
      exit_shell (last_command_exit_value);
#else
      with_input_from_string (command_execution_string, "-c");
      goto read_and_execute;
#endif
    }


  if (shell_script_filename)
    open_shell_script (shell_script_filename);
  else if (interactive == 0)
    {


#if defined (BUFFERED_INPUT)
      default_buffered_input = fileno (stdin);
#else
      setbuf (default_input, (char *)NULL);
#endif
      read_from_stdin = 1;
    }
  else if (top_level_arg_index == argc)


    read_from_stdin = 1;

  set_bash_input ();

  if (debugging_mode && locally_skip_execution == 0 && running_setuid == 0 && (reading_shell_script || interactive_shell == 0))
    start_debugger ();


  if (interactive_shell)
    {

      reset_mail_timer ();
      init_mail_dates ();

#if defined (HISTORY)

      bash_initialize_history ();


      if (shell_initialized == 0 && history_lines_this_session == 0)
	load_history ();
#endif


      get_tty_state ();
    }

#if !defined (ONESHOT)
 read_and_execute:
#endif

  shell_initialized = 1;

  if (pretty_print_mode && interactive_shell)
    {
      internal_warning (_("pretty-printing mode ignored in interactive shells"));
      pretty_print_mode = 0;
    }
  if (pretty_print_mode)
    exit_shell (pretty_print_loop ());


  reader_loop ();
  exit_shell (last_command_exit_value);
}
