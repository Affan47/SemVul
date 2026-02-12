bash_directory_completion_hook (dirname)
     char **dirname;
{
  char *local_dirname, *new_dirname, *t;
  int return_value, should_expand_dirname, nextch, closer;
  WORD_LIST *wl;

  return_value = should_expand_dirname = nextch = closer = 0;
  local_dirname = *dirname;

  if (t = mbschr (local_dirname, '$'))
    {
      should_expand_dirname = '$';
      nextch = t[1];


      if (nextch == '(')
	closer = ')';
      else if (nextch == '{')
	closer = '}';
      else
	nextch = 0;

      if (closer)
	{
	  int p;
	  char delims[2];

	  delims[0] = closer; delims[1] = 0;
	  p = skip_to_delim (t, 1, delims, SD_NOJMP|SD_COMPLETE);
	  if (t[p] != closer)
	    should_expand_dirname = 0;
	}
    }
  else if (local_dirname[0] == '~')
    should_expand_dirname = '~';
  else
    {
      t = mbschr (local_dirname, '`');
      if (t && unclosed_pair (local_dirname, strlen (local_dirname), "`") == 0)
	should_expand_dirname = '`';
    }

  if (should_expand_dirname && directory_exists (local_dirname, 1))
    should_expand_dirname = 0;

  if (should_expand_dirname)
    {
      new_dirname = savestring (local_dirname);
      wl = expand_prompt_string (new_dirname, 0, W_NOCOMSUB|W_NOPROCSUB|W_COMPLETE);
      if (wl)
	{
	  *dirname = string_list (wl);


	  return_value = STREQ (local_dirname, *dirname) == 0;
	  free (local_dirname);
	  free (new_dirname);
	  dispose_words (wl);
	  local_dirname = *dirname;


	  if (rl_filename_quote_characters && *rl_filename_quote_characters)
	    {
	      int i, j, c;
	      i = strlen (default_filename_quote_characters);
	      custom_filename_quote_characters = xrealloc (custom_filename_quote_characters, i+1);
	      for (i = j = 0; c = default_filename_quote_characters[i]; i++)
		{
		  if (c == should_expand_dirname || c == nextch || c == closer)
		    continue;
		  custom_filename_quote_characters[j++] = c;
		}
	      custom_filename_quote_characters[j] = '\0';
	      rl_filename_quote_characters = custom_filename_quote_characters;
	      set_filename_bstab (rl_filename_quote_characters);
	    }
	}
      else
	{
	  free (new_dirname);
	  free (local_dirname);
	  *dirname = (char *)xmalloc (1);
	  **dirname = '\0';
	  return 1;
	}
    }
  else
    {

      new_dirname = bash_dequote_filename (local_dirname, rl_completion_quote_character);
      return_value = STREQ (local_dirname, new_dirname) == 0;
      free (local_dirname);
      local_dirname = *dirname = new_dirname;
    }


  if (no_symbolic_links == 0 && (local_dirname[0] != '.' || local_dirname[1]))
    {
      char *temp1, *temp2;
      int len1, len2;


      t = get_working_directory ("symlink-hook");
      temp1 = make_absolute (local_dirname, t);
      free (t);
      temp2 = sh_canonpath (temp1, PATH_CHECKDOTDOT|PATH_CHECKEXISTS);


      if (temp2 == 0 && dircomplete_spelling && dircomplete_expand)
	{
	  temp2 = dirspell (temp1);
	  if (temp2)
	    {
	      free (temp1);
	      temp1 = temp2;
	      temp2 = sh_canonpath (temp1, PATH_CHECKDOTDOT|PATH_CHECKEXISTS);
	      return_value |= temp2 != 0;
	    }
	}

      if (temp2 == 0)
	{
	  free (temp1);
	  return return_value;
	}
      len1 = strlen (temp1);
      if (temp1[len1 - 1] == '/')
	{
	  len2 = strlen (temp2);
	  if (len2 > 2)
	    {
	      temp2 = (char *)xrealloc (temp2, len2 + 2);
	      temp2[len2] = '/';
	      temp2[len2 + 1] = '\0';
	    }
	}


      if (dircomplete_expand_relpath || ((local_dirname[0] != '/' && local_dirname[0] != '.') && STREQ (temp1, temp2) == 0))
	return_value |= STREQ (local_dirname, temp2) == 0;
      free (local_dirname);
      *dirname = temp2;
      free (temp1);
    }

  return (return_value);
}
