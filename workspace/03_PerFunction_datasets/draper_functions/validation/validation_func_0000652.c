display_backtrace_file_and_line (SCM frame, SCM port, scm_print_state *pstate)
{
  SCM file, line;

  display_backtrace_get_file_line (frame, &file, &line);

  if (scm_is_eq (SCM_PACK (SCM_SHOW_FILE_NAME), sym_base))
    {
      if (scm_is_false (file))
	{
	  if (scm_is_false (line))
	    scm_putc ('?', port);
	  else
	    scm_puts ("<stdin>", port);
	}
      else
	{
	  pstate -> writingp = 0;
#ifdef HAVE_POSIX
	  scm_iprin1 ((scm_is_string (file)?
		       scm_basename (file, SCM_UNDEFINED) : file),
		      port, pstate);
#else
	  scm_iprin1 (file, port, pstate);
#endif
	  pstate -> writingp = 1;
	}

      scm_putc (':', port);
    }
  else if (scm_is_true (line))
    {
      int i, j=0;
      for (i = scm_to_int (line)+1; i > 0; i = i/10, j++)
	;
      indent (4-j, port);
    }

  if (scm_is_false (line))
    scm_puts ("   ?", port);
  else
    scm_intprint (scm_to_int (line) + 1, 10, port);
  scm_puts (": ", port);
}
