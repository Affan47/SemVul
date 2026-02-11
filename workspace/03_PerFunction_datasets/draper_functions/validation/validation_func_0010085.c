new_include_prefix (prev_file_name, prefix, name)
     struct file_name_list *prev_file_name;
     char *prefix;
     char *name;
{
  if (!name)
    fatal ("Directory name missing after command line option");

  if (!*name)

    return 0;
  else {
    struct file_name_list *dir
      = ((struct file_name_list *)
	 xmalloc (sizeof (struct file_name_list)
		  + strlen (prefix) + strlen (name) + 1 ));
    size_t len;
    strcpy (dir->fname, prefix);
    strcat (dir->fname, name);
    len = simplify_filename (dir->fname);


    if (len && dir->fname[len - 1] != '/') {
      if (len == 1 && dir->fname[len - 1] == '.')
	len = 0;
      else
	dir->fname[len++] = '/';
      dir->fname[len] = 0;
    }


    if (prev_file_name && !strcmp (prev_file_name->fname, dir->fname)) {

      if (!first_bracket_include)
	first_bracket_include = prev_file_name;
      free (dir);
      return 0;
    }

#if (!defined(VMS) && !defined(_WIN32)) || defined(__CYGWIN32__)


    if (stat (len ? dir->fname : ".", &dir->st) != 0) {
      if (errno != ENOENT && errno != ENOTDIR)
	error_from_errno (dir->fname);
      free (dir);
      return 0;
    }


    if (prev_file_name
	&& INO_T_EQ (prev_file_name->st.st_ino, dir->st.st_ino)
	&& prev_file_name->st.st_dev == dir->st.st_dev) {

      if (!first_bracket_include)
	first_bracket_include = prev_file_name;
      free (dir);
      return 0;
    }
#endif

    dir->next = 0;
    dir->c_system_include_path = 0;
    dir->got_name_map = 0;

    return dir;
  }
}
