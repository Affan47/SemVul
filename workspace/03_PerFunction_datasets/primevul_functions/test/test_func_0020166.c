exit_shell (s)
     int s;
{
  fflush (stdout);
  fflush (stderr);


#if defined (READLINE)
  if (RL_ISSTATE (RL_STATE_TERMPREPPED) && rl_deprep_term_function)
    (*rl_deprep_term_function) ();
#endif
  if (read_tty_modified ())
    read_tty_cleanup ();


  if (signal_is_trapped (0))
    s = run_exit_trap ();

#if defined (PROCESS_SUBSTITUTION)
  unlink_fifo_list ();
#endif

#if defined (HISTORY)
  if (remember_on_history)
    maybe_save_shell_history ();
#endif

#if defined (COPROCESS_SUPPORT)
  coproc_flush ();
#endif

#if defined (JOB_CONTROL)


  if (interactive_shell && login_shell && hup_on_exit)
    hangup_all_jobs ();


  if (subshell_environment == 0)
    end_job_control ();
#endif


  sh_exit (s);
}
