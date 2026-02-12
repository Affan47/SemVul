initialize_shell_variables (env, privmode)
     char **env;
     int privmode;
{
  char *name, *string, *temp_string;
  int c, char_index, string_index, string_length, ro;
  SHELL_VAR *temp_var;

  create_variable_tables ();

  for (string_index = 0; string = env[string_index++]; )
    {
      char_index = 0;
      name = string;
      while ((c = *string++) && c != '=')
	;
      if (string[-1] == '=')
	char_index = string - name - 1;

      if (char_index == 0)
	continue;

      name[char_index] = '\0';

      temp_var = (SHELL_VAR *)NULL;

      if (privmode == 0 && read_but_dont_execute == 0 && STREQN ("() {", string, 4))
	{
	  string_length = strlen (string);
	  temp_string = (char *)xmalloc (3 + string_length + char_index);

	  strcpy (temp_string, name);
	  temp_string[char_index] = ' ';
	  strcpy (temp_string + char_index + 1, string);

	  parse_and_execute (temp_string, name, SEVAL_NONINT|SEVAL_NOHIST);

	  if (name[char_index - 1] == ')' && name[char_index - 2] == '(')
	    name[char_index - 2] = '\0';

	  if (temp_var = find_function (name))
	    {
	      VSETATTR (temp_var, (att_exported|att_imported));
	      array_needs_making = 1;
	    }
	  else
	    {
	      last_command_exit_value = 1;
	      report_error (_("error importing function definition for `%s'"), name);
	    }

	  if (name[char_index - 1] == ')' && name[char_index - 2] == '\0')
	    name[char_index - 2] = '(';
	}
#if defined (ARRAY_VARS)
#  if 0

      else if (*string == '(' && string[1] == '[' && string[strlen (string) - 1] == ')')
	{
	  string_length = 1;
	  temp_string = extract_array_assignment_list (string, &string_length);
	  temp_var = assign_array_from_string (name, temp_string);
	  FREE (temp_string);
	  VSETATTR (temp_var, (att_exported | att_imported));
	  array_needs_making = 1;
	}
#  endif
#endif
#if 0
      else if (legal_identifier (name))
#else
      else
#endif
	{
	  ro = 0;
	  if (posixly_correct && STREQ (name, "SHELLOPTS"))
	    {
	      temp_var = find_variable ("SHELLOPTS");
	      ro = temp_var && readonly_p (temp_var);
	      if (temp_var)
		VUNSETATTR (temp_var, att_readonly);
	    }
	  temp_var = bind_variable (name, string, 0);
	  if (temp_var)
	    {
	      if (legal_identifier (name))
		VSETATTR (temp_var, (att_exported | att_imported));
	      else
		VSETATTR (temp_var, (att_exported | att_imported | att_invisible));
	      if (ro)
		VSETATTR (temp_var, att_readonly);
	      array_needs_making = 1;
	    }
	}

      name[char_index] = '=';

      if (temp_var && function_p (temp_var) == 0)
	{
	  CACHE_IMPORTSTR (temp_var, name);
	}
    }

  set_pwd ();

  temp_var = set_if_not ("_", dollar_vars[0]);

  dollar_dollar_pid = getpid ();

  temp_var = set_if_not ("PATH", DEFAULT_PATH_VALUE);
#if 0
  set_auto_export (temp_var);
#endif

  temp_var = set_if_not ("TERM", "dumb");
#if 0
  set_auto_export (temp_var);
#endif

#if defined (__QNX__)

  {
    char node_name[22];
#  if defined (__QNXNTO__)
    netmgr_ndtostr(ND2S_LOCAL_STR, ND_LOCAL_NODE, node_name, sizeof(node_name));
#  else
    qnx_nidtostr (getnid (), node_name, sizeof (node_name));
#  endif
    temp_var = bind_variable ("NODE", node_name, 0);
    set_auto_export (temp_var);
  }
#endif

  if (interactive_shell)
    {
#if defined (PROMPT_STRING_DECODE)
      set_if_not ("PS1", primary_prompt);
#else
      if (current_user.uid == -1)
	get_current_user_info ();
      set_if_not ("PS1", current_user.euid == 0 ? "# " : primary_prompt);
#endif
      set_if_not ("PS2", secondary_prompt);
    }
  set_if_not ("PS4", "+ ");

  temp_var = bind_variable ("IFS", " \t\n", 0);
  setifs (temp_var);

  set_machine_vars ();

  if (interactive_shell)
    {
      temp_var = set_if_not ("MAILCHECK", posixly_correct ? "600" : "60");
      VSETATTR (temp_var, att_integer);
    }

  initialize_shell_level ();

  set_ppid ();

  temp_var = bind_variable ("OPTIND", "1", 0);
  VSETATTR (temp_var, att_integer);
  getopts_reset (0);
  bind_variable ("OPTERR", "1", 0);
  sh_opterr = 1;

  if (login_shell == 1 && posixly_correct == 0)
    set_home_var ();

  name = get_bash_name ();
  temp_var = bind_variable ("BASH", name, 0);
  free (name);

  set_shell_var ();

  bind_variable ("BASH_VERSION", shell_version_string (), 0);
#if defined (ARRAY_VARS)
  make_vers_array ();
#endif

  if (command_execution_string)
    bind_variable ("BASH_EXECUTION_STRING", command_execution_string, 0);

  temp_var = find_variable ("POSIXLY_CORRECT");
  if (!temp_var)
    temp_var = find_variable ("POSIX_PEDANTIC");
  if (temp_var && imported_p (temp_var))
    sv_strict_posix (temp_var->name);

#if defined (HISTORY)

  if (remember_on_history)
    {
      name = bash_tilde_expand (posixly_correct ? "~/.sh_history" : "~/.bash_history", 0);

      set_if_not ("HISTFILE", name);
      free (name);
    }
#endif

  seedrand ();

  if (interactive_shell)
    {
      temp_var = find_variable ("IGNOREEOF");
      if (!temp_var)
	temp_var = find_variable ("ignoreeof");
      if (temp_var && imported_p (temp_var))
	sv_ignoreeof (temp_var->name);
    }

#if defined (HISTORY)
  if (interactive_shell && remember_on_history)
    {
      sv_history_control ("HISTCONTROL");
      sv_histignore ("HISTIGNORE");
      sv_histtimefmt ("HISTTIMEFORMAT");
    }
#endif

#if defined (READLINE) && defined (STRICT_POSIX)

  if (interactive_shell && posixly_correct && no_line_editing == 0)
    rl_prefer_env_winsize = 1;
#endif

#if 0
  temp_var = find_variable ("SSH_CLIENT");
  if (temp_var && imported_p (temp_var))
    {
      VUNSETATTR (temp_var, att_exported);
      array_needs_making = 1;
    }
  temp_var = find_variable ("SSH2_CLIENT");
  if (temp_var && imported_p (temp_var))
    {
      VUNSETATTR (temp_var, att_exported);
      array_needs_making = 1;
    }
#endif

  uidset ();

  temp_var = find_variable ("BASH_XTRACEFD");
  if (temp_var && imported_p (temp_var))
    sv_xtracefd (temp_var->name);

  initialize_dynamic_variables ();
}
}
