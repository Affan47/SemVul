shell_reinitialize ()
{

  primary_prompt = PPROMPT;
  secondary_prompt = SPROMPT;


  current_command_number = 1;


  no_rc = no_profile = 1;


  login_shell = make_login_shell = interactive = executing = 0;
  debugging = do_version = line_number = last_command_exit_value = 0;
  forced_interactive = interactive_shell = 0;
  subshell_environment = running_in_background = 0;
  expand_aliases = 0;
  bash_argv_initialized = 0;


#if defined (HISTORY)
  bash_history_reinit (enable_history_list = 0);
#endif

#if defined (RESTRICTED_SHELL)
  restricted = 0;
#endif


  bashrc_file = DEFAULT_BASHRC;


  delete_all_contexts (shell_variables);
  delete_all_variables (shell_functions);

  reinit_special_variables ();

#if defined (READLINE)
  bashline_reinitialize ();
#endif

  shell_reinitialized = 1;
}
