bash_filename_stat_hook (dirname)
     char **dirname;
{
  char *local_dirname, *new_dirname, *t;
  int should_expand_dirname, return_value;
  int global_nounset;
  WORD_LIST *wl;

  local_dirname = *dirname;
  should_expand_dirname = return_value = 0;
  if (t = mbschr (local_dirname, '$'))
    should_expand_dirname = '$';
  else if (t = mbschr (local_dirname, '`'))
    should_expand_dirname = '`';

  if (should_expand_dirname && directory_exists (local_dirname, 0))
    should_expand_dirname = 0;

  if (should_expand_dirname)
    {
      new_dirname = savestring (local_dirname);


      global_nounset = unbound_vars_is_error;
      unbound_vars_is_error = 0;
      wl = expand_prompt_string (new_dirname, 0, W_NOCOMSUB|W_NOPROCSUB|W_COMPLETE);
      unbound_vars_is_error = global_nounset;
      if (wl)
	{
	  free (new_dirname);
	  new_dirname = string_list (wl);


	  if (new_dirname && *new_dirname)
	    {
	      free (local_dirname);
	      local_dirname = *dirname = new_dirname;
	      return_value = STREQ (local_dirname, *dirname) == 0;
	    }
	  else
	    free (new_dirname);
	  dispose_words (wl);
	}
      else
	free (new_dirname);
    }


  if (no_symbolic_links == 0 && (local_dirname[0] != '.' || local_dirname[1]))
    {
      char *temp1, *temp2;

      t = get_working_directory ("symlink-hook");
      temp1 = make_absolute (local_dirname, t);
      free (t);
      temp2 = sh_canonpath (temp1, PATH_CHECKDOTDOT|PATH_CHECKEXISTS);


      if (temp2 == 0)
	{
	  free (temp1);
	  return return_value;
	}

      free (local_dirname);
      *dirname = temp2;
      free (temp1);
    }

  return (return_value);
}
