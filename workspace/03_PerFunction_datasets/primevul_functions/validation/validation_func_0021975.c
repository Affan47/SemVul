process_copy_pass (void)
{
  dynamic_string input_name = DYNAMIC_STRING_INITIALIZER;

  dynamic_string output_name = DYNAMIC_STRING_INITIALIZER;

  size_t dirname_len;
  int res;
  char *slash;
  struct stat in_file_stat;
  struct stat out_file_stat;
  int in_file_des;
  int out_file_des;
  int existing_dir;

  newdir_umask = umask (0);


  dirname_len = strlen (directory_name);
  if (change_directory_option && !ISSLASH (directory_name[0]))
    {
      char *pwd = xgetcwd ();

      ds_concat (&output_name, pwd);
      ds_append (&output_name, '/');
    }
  ds_concat (&output_name, directory_name);
  ds_append (&output_name, '/');
  dirname_len = ds_len (&output_name);
  output_is_seekable = true;

  change_dir ();


  while (ds_fgetstr (stdin, &input_name, name_end) != NULL)
    {
      int link_res = -1;


      if (input_name.ds_string[0] == '\0')
	{
	  error (0, 0, _("blank line ignored"));
	  continue;
	}


      if (input_name.ds_string[0] == '.'
	  && (input_name.ds_string[1] == '\0'
	      || (input_name.ds_string[1] == '/'
		  && input_name.ds_string[2] == '\0')))
	continue;

      if ((*xstat) (input_name.ds_string, &in_file_stat) < 0)
	{
	  stat_error (input_name.ds_string);
	  continue;
	}


      for (slash = input_name.ds_string; *slash == '/'; ++slash)
	;
      ds_reset (&output_name, dirname_len);
      ds_concat (&output_name, slash);

      existing_dir = false;
      if (lstat (output_name.ds_string, &out_file_stat) == 0)
	{
	  if (S_ISDIR (out_file_stat.st_mode)
	      && S_ISDIR (in_file_stat.st_mode))
	    {


	      existing_dir = true;
	    }
	  else if (!unconditional_flag
		   && in_file_stat.st_mtime <= out_file_stat.st_mtime)
	    {
	      error (0, 0, _("%s not created: newer or same age version exists"),
		     output_name.ds_string);
	      continue;
	    }
	  else if (S_ISDIR (out_file_stat.st_mode)
			? rmdir (output_name.ds_string)
			: unlink (output_name.ds_string))
	    {
	      error (0, errno, _("cannot remove current %s"),
		     output_name.ds_string);
	      continue;
	    }
	}


      if (S_ISREG (in_file_stat.st_mode))
	{


	  if (link_flag)


	    link_res = link_to_name (output_name.ds_string,
				     input_name.ds_string);
	  if ( (link_res < 0) && (in_file_stat.st_nlink > 1) )
	    link_res = link_to_maj_min_ino (output_name.ds_string,
				major (in_file_stat.st_dev),
				minor (in_file_stat.st_dev),
				in_file_stat.st_ino);


	  if (link_res < 0)
	    {
	      in_file_des = open (input_name.ds_string,
				  O_RDONLY | O_BINARY, 0);
	      if (in_file_des < 0)
		{
		  open_error (input_name.ds_string);
		  continue;
		}
	      out_file_des = open (output_name.ds_string,
				   O_CREAT | O_WRONLY | O_BINARY, 0600);
	      if (out_file_des < 0 && create_dir_flag)
		{
		  create_all_directories (output_name.ds_string);
		  out_file_des = open (output_name.ds_string,
				       O_CREAT | O_WRONLY | O_BINARY, 0600);
		}
	      if (out_file_des < 0)
		{
		  open_error (output_name.ds_string);
		  close (in_file_des);
		  continue;
		}

	      copy_files_disk_to_disk (in_file_des, out_file_des, in_file_stat.st_size, input_name.ds_string);
	      disk_empty_output_buffer (out_file_des, true);

	      set_copypass_perms (out_file_des,
				  output_name.ds_string, &in_file_stat);

	      if (reset_time_flag)
                {
                  set_file_times (in_file_des,
				  input_name.ds_string,
                                  in_file_stat.st_atime,
                                  in_file_stat.st_mtime);
                  set_file_times (out_file_des,
				  output_name.ds_string,
                                  in_file_stat.st_atime,
                                  in_file_stat.st_mtime);
	        }

	      if (close (in_file_des) < 0)
		close_error (input_name.ds_string);

	      if (close (out_file_des) < 0)
		close_error (output_name.ds_string);

	      warn_if_file_changed(input_name.ds_string, in_file_stat.st_size,
                                   in_file_stat.st_mtime);
	    }
	}
      else if (S_ISDIR (in_file_stat.st_mode))
	{
	  struct cpio_file_stat file_stat;

	  stat_to_cpio (&file_stat, &in_file_stat);
	  file_stat.c_name = output_name.ds_string;
	  cpio_create_dir (&file_stat, existing_dir);
	}
      else if (S_ISCHR (in_file_stat.st_mode) ||
	       S_ISBLK (in_file_stat.st_mode) ||
#ifdef S_ISFIFO
	       S_ISFIFO (in_file_stat.st_mode) ||
#endif
#ifdef S_ISSOCK
	       S_ISSOCK (in_file_stat.st_mode) ||
#endif
	       0)
	{


	  if (link_flag)

	    link_res = link_to_name (output_name.ds_string,
				     input_name.ds_string);
	  if ( (link_res < 0) && (in_file_stat.st_nlink > 1) )
	    link_res = link_to_maj_min_ino (output_name.ds_string,
			major (in_file_stat.st_dev),
			minor (in_file_stat.st_dev),
			in_file_stat.st_ino);

	  if (link_res < 0)
	    {
	      res = mknod (output_name.ds_string, in_file_stat.st_mode,
			   in_file_stat.st_rdev);
	      if (res < 0 && create_dir_flag)
		{
		  create_all_directories (output_name.ds_string);
		  res = mknod (output_name.ds_string, in_file_stat.st_mode,
			       in_file_stat.st_rdev);
		}
	      if (res < 0)
		{
		  mknod_error (output_name.ds_string);
		  continue;
		}
	      set_copypass_perms (-1, output_name.ds_string, &in_file_stat);
	    }
	}

#ifdef S_ISLNK
      else if (S_ISLNK (in_file_stat.st_mode))
	{
	  char *link_name;
	  int link_size;
	  link_name = (char *) xmalloc ((unsigned int) in_file_stat.st_size + 1);

	  link_size = readlink (input_name.ds_string, link_name,
			        in_file_stat.st_size);
	  if (link_size < 0)
	    {
	      readlink_error (input_name.ds_string);
	      free (link_name);
	      continue;
	    }
	  link_name[link_size] = '\0';

	  res = UMASKED_SYMLINK (link_name, output_name.ds_string,
				 in_file_stat.st_mode);
	  if (res < 0 && create_dir_flag)
	    {
	      create_all_directories (output_name.ds_string);
	      res = UMASKED_SYMLINK (link_name, output_name.ds_string,
				     in_file_stat.st_mode);
	    }
	  if (res < 0)
	    {
	      symlink_error (output_name.ds_string, link_name);
	      free (link_name);
	      continue;
	    }


	  if (!no_chown_flag)
            {
              uid_t uid = set_owner_flag ? set_owner : in_file_stat.st_uid;
              gid_t gid = set_group_flag ? set_group : in_file_stat.st_gid;
	      if ((lchown (output_name.ds_string, uid, gid) < 0)
		  && errno != EPERM)
	        chown_error_details (output_name.ds_string, uid, gid);
            }
	  free (link_name);
	}
#endif
      else
	{
	  error (0, 0, _("%s: unknown file type"), input_name.ds_string);
	}

      if (verbose_flag)
	fprintf (stderr, "%s\n", output_name.ds_string);
      if (dot_flag)
	fputc ('.', stderr);
    }

  if (dot_flag)
    fputc ('\n', stderr);

  apply_delayed_set_stat ();

  if (!quiet_flag)
    {
      size_t blocks = (output_bytes + io_block_size - 1) / io_block_size;
      fprintf (stderr,
	       ngettext ("%lu block\n", "%lu blocks\n",
			 (unsigned long) blocks),
	       (unsigned long) blocks);
    }

  ds_free (&input_name);
  ds_free (&output_name);
}
