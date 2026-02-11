bash_default_completion (text, start, end, qc, compflags)
     const char *text;
     int start, end, qc, compflags;
{
  char **matches;

  matches = (char **)NULL;


  if (!matches && *text == '$')
    {
      if (qc != '\'' && text[1] == '(')
	matches = rl_completion_matches (text, command_subst_completion_function);
      else
	matches = rl_completion_matches (text, variable_completion_function);
    }


  if (matches ==0 && *text == '~' && mbschr (text, '/') == 0)
    matches = rl_completion_matches (text, rl_username_completion_function);


  if (!matches && perform_hostname_completion && *text == '@')
    matches = rl_completion_matches (text, hostname_completion_function);


  if (matches == 0 && (compflags & DEFCOMP_CMDPOS))
    {


      if (no_empty_command_completion && end == start && text[0] == '\0')
	{
	  matches = (char **)NULL;
	  rl_ignore_some_completions_function = bash_ignore_everything;
	}
      else
	{
#define CMD_IS_DIR(x)	(absolute_pathname(x) == 0 && absolute_program(x) == 0 && *(x) != '~' && test_for_directory (x))

	  dot_in_path = 0;
	  matches = rl_completion_matches (text, command_word_completion_function);


	  if (matches == (char **)NULL)
	    rl_ignore_some_completions_function = bash_ignore_filenames;
	  else if (matches[1] == 0 && CMD_IS_DIR(matches[0]) && dot_in_path == 0)


	    {
	      rl_completion_suppress_append = 1;
	      rl_filename_completion_desired = 0;
	    }
	  else if (matches[0] && matches[1] && STREQ (matches[0], matches[1]) && CMD_IS_DIR (matches[0]))


	    {
	      rl_completion_suppress_append = 1;
	      rl_filename_completion_desired = 0;
	    }
	}
    }


  if (!matches && glob_pattern_p (text))
    {
      matches = rl_completion_matches (text, glob_complete_word);


      if (matches && matches[1] && rl_completion_type == TAB)
	{
	  strvec_dispose (matches);
	  matches = (char **)0;
	}
    }

  return (matches);
}
