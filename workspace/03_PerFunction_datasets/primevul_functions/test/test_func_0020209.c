command_word_completion_function (hint_text, state)
     const char *hint_text;
     int state;
{
  static char *hint = (char *)NULL;
  static char *path = (char *)NULL;
  static char *val = (char *)NULL;
  static char *filename_hint = (char *)NULL;
  static char *fnhint = (char *)NULL;
  static char *dequoted_hint = (char *)NULL;
  static char *directory_part = (char *)NULL;
  static char **glob_matches = (char **)NULL;
  static int path_index, hint_len, istate, igncase;
  static int mapping_over, local_index, searching_path, hint_is_dir;
  static int old_glob_ignore_case, globpat;
  static SHELL_VAR **varlist = (SHELL_VAR **)NULL;
#if defined (ALIAS)
  static alias_t **alias_list = (alias_t **)NULL;
#endif
  char *temp, *cval;


  if (state == 0)
    {
      rl_filename_stat_hook = bash_command_name_stat_hook;

      if (dequoted_hint && dequoted_hint != hint)
	free (dequoted_hint);
      if (hint)
	free (hint);

      mapping_over = searching_path = 0;
      hint_is_dir = CMD_IS_DIR (hint_text);
      val = (char *)NULL;

      temp = rl_variable_value ("completion-ignore-case");
      igncase = RL_BOOLEAN_VARIABLE_VALUE (temp);

      if (glob_matches)
	{
	  free (glob_matches);
	  glob_matches = (char **)NULL;
	}

      globpat = completion_glob_pattern ((char *)hint_text);


      if (globpat || absolute_program (hint_text))
	{


	  if (*hint_text == '~')
	    {
	      hint = bash_tilde_expand (hint_text, 0);
	      directory_part = savestring (hint_text);
	      temp = strchr (directory_part, '/');
	      if (temp)
		*temp = 0;
	      else
		{
		  free (directory_part);
		  directory_part = (char *)NULL;
		}
	    }
	  else if (dircomplete_expand)
	    {
	      hint = savestring (hint_text);
	      bash_directory_completion_hook (&hint);
	    }
	  else
	    hint = savestring (hint_text);

	  dequoted_hint = hint;


	  if (rl_completion_found_quote && rl_completion_quote_character == 0)
	    {
	      dequoted_hint = bash_dequote_filename (hint, 0);
	      free (hint);
	      hint = dequoted_hint;
	    }
	  hint_len = strlen (hint);

	  if (filename_hint)
	    free (filename_hint);

	  fnhint = filename_hint = savestring (hint);

	  istate = 0;

	  if (globpat)
	    {
	      mapping_over = 5;
	      goto globword;
	    }
	  else
	    {
	     if (dircomplete_expand && path_dot_or_dotdot (filename_hint))
		{
		  dircomplete_expand = 0;
		  set_directory_hook ();
		  dircomplete_expand = 1;
		}
	      mapping_over = 4;
	      goto inner;
	    }
	}

      dequoted_hint = hint = savestring (hint_text);
      hint_len = strlen (hint);

      if (rl_completion_found_quote && rl_completion_quote_character == 0)
	dequoted_hint = bash_dequote_filename (hint, 0);

      path = get_string_value ("PATH");
      path_index = dot_in_path = 0;


      local_index = 0;

      if (varlist)
	free (varlist);

      varlist = all_visible_functions ();

#if defined (ALIAS)
      if (alias_list)
	free (alias_list);

      alias_list = all_aliases ();
#endif
    }


  switch (mapping_over)
    {
    case 0:
#if defined (ALIAS)
      while (alias_list && alias_list[local_index])
	{
	  register char *alias;

	  alias = alias_list[local_index++]->name;

	  if (igncase == 0 && (STREQN (alias, hint, hint_len)))
	    return (savestring (alias));
	  else if (igncase && strncasecmp (alias, hint, hint_len) == 0)
	    return (savestring (alias));
	}
#endif
      local_index = 0;
      mapping_over++;

    case 1:
      {
	while (word_token_alist[local_index].word)
	  {
	    register char *reserved_word;

	    reserved_word = word_token_alist[local_index++].word;

	    if (STREQN (reserved_word, hint, hint_len))
	      return (savestring (reserved_word));
	  }
	local_index = 0;
	mapping_over++;
      }

    case 2:
      while (varlist && varlist[local_index])
	{
	  register char *varname;

	  varname = varlist[local_index++]->name;


	  if (igncase == 0 && (STREQN (varname, hint, hint_len)))
	    return (savestring (varname));
	  else if (igncase && strncasecmp (varname, hint, hint_len) == 0)
	    return (savestring (varname));
	}
      local_index = 0;
      mapping_over++;

    case 3:
      for (; local_index < num_shell_builtins; local_index++)
	{


	  if (!shell_builtins[local_index].function ||
	      (shell_builtins[local_index].flags & BUILTIN_ENABLED) == 0)
	    continue;

	  if (STREQN (shell_builtins[local_index].name, hint, hint_len))
	    {
	      int i = local_index++;

	      return (savestring (shell_builtins[i].name));
	    }
	}
      local_index = 0;
      mapping_over++;
    }

globword:


  if (globpat)
    {
      if (state == 0)
	{
	  glob_ignore_case = igncase;
	  glob_matches = shell_glob_filename (hint);
	  glob_ignore_case = old_glob_ignore_case;

	  if (GLOB_FAILED (glob_matches) || glob_matches == 0)
	    {
	      glob_matches = (char **)NULL;
	      return ((char *)NULL);
	    }

	  local_index = 0;

	  if (glob_matches[1] && rl_completion_type == TAB)
	    return ((char *)NULL);
	}

      while (val = glob_matches[local_index++])
        {
	  if (executable_or_directory (val))
	    {
	      if (*hint_text == '~' && directory_part)
		{
		  temp = maybe_restore_tilde (val, directory_part);
		  free (val);
		  val = temp;
		}
	      return (val);
	    }
	  free (val);
        }

      glob_ignore_case = old_glob_ignore_case;
      return ((char *)NULL);
    }


  if (hint_is_dir)
    {
      hint_is_dir = 0;
      return (savestring (hint_text));
    }


 outer:

  istate = (val != (char *)NULL);

  if (istate == 0)
    {
      char *current_path;


      if (path == 0 || path[path_index] == 0 ||
	  (current_path = extract_colon_unit (path, &path_index)) == 0)
	return ((char *)NULL);

      searching_path = 1;
      if (*current_path == 0)
	{
	  free (current_path);
	  current_path = savestring (".");
	}

      if (*current_path == '~')
	{
	  char *t;

	  t = bash_tilde_expand (current_path, 0);
	  free (current_path);
	  current_path = t;
	}

      if (current_path[0] == '.' && current_path[1] == '\0')
	dot_in_path = 1;

      if (fnhint && fnhint != filename_hint)
	free (fnhint);
      if (filename_hint)
	free (filename_hint);

      filename_hint = sh_makepath (current_path, hint, 0);


      if (strpbrk (filename_hint, "\"'\\"))
	fnhint = sh_backslash_quote (filename_hint, filename_bstab, 0);
      else
	fnhint = filename_hint;
      free (current_path);
    }

 inner:
  val = rl_filename_completion_function (fnhint, istate);
  if (mapping_over == 4 && dircomplete_expand)
    set_directory_hook ();

  istate = 1;

  if (val == 0)
    {


      if (absolute_program (hint))
	return ((char *)NULL);

      goto outer;
    }
  else
    {
      int match, freetemp;

      if (absolute_program (hint))
	{
	  if (igncase == 0)
	    match = strncmp (val, hint, hint_len) == 0;
	  else
	    match = strncasecmp (val, hint, hint_len) == 0;


	  if (*hint_text == '~')
	    temp = maybe_restore_tilde (val, directory_part);
	  else
	    temp = savestring (val);
	  freetemp = 1;
	}
      else
	{
	  temp = strrchr (val, '/');

	  if (temp)
	    {
	      temp++;
	      if (igncase == 0)
		freetemp = match = strncmp (temp, hint, hint_len) == 0;
	      else
		freetemp = match = strncasecmp (temp, hint, hint_len) == 0;
	      if (match)
		temp = savestring (temp);
	    }
	  else
	    freetemp = match = 0;
	}


#if 0


      if (match && searching_path == 0 && *val == '.')
	{
	  char *t, *t1;

	  t = get_working_directory ("command-word-completion");
	  t1 = make_absolute (val, t);
	  free (t);
	  cval = sh_canonpath (t1, PATH_CHECKDOTDOT|PATH_CHECKEXISTS);
	}
      else
#endif
	cval = val;

      if (match && executable_completion ((searching_path ? val : cval), searching_path))
	{
	  if (cval != val)
	    free (cval);
	  free (val);
	  val = "";
	  return (temp);
	}
      else
	{
	  if (freetemp)
	    free (temp);
	  if (cval != val)
	    free (cval);
	  free (val);
	  goto inner;
	}
    }
}
