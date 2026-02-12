shell_initialize ()
{
  char hostname[256];
  int should_be_restricted;


  if (shell_initialized == 0)
    {
      sh_setlinebuf (stderr);
      sh_setlinebuf (stdout);
    }


  initialize_shell_builtins ();


  initialize_traps ();
  initialize_signals (0);


  if (current_host_name == 0)
    {

      if (gethostname (hostname, 255) < 0)
	current_host_name = "??host??";
      else
	current_host_name = savestring (hostname);
    }


  if (interactive_shell)
    get_current_user_info ();


  tilde_initialize ();

#if defined (RESTRICTED_SHELL)
  should_be_restricted = shell_is_restricted (shell_name);
#endif


#if defined (RESTRICTED_SHELL)
  initialize_shell_variables (shell_environment, privileged_mode||restricted||should_be_restricted||running_setuid);
#else
  initialize_shell_variables (shell_environment, privileged_mode||running_setuid);
#endif


  initialize_job_control (jobs_m_flag);


  initialize_bash_input ();

  initialize_flags ();


#if defined (RESTRICTED_SHELL)
  initialize_shell_options (privileged_mode||restricted||should_be_restricted||running_setuid);
  initialize_bashopts (privileged_mode||restricted||should_be_restricted||running_setuid);
#else
  initialize_shell_options (privileged_mode||running_setuid);
  initialize_bashopts (privileged_mode||running_setuid);
#endif
}
