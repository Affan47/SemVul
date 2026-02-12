get_next_reel (int tape_des)
{
  static int reel_number = 1;
  FILE *tty_in;
  FILE *tty_out;
  int old_tape_des;
  char *next_archive_name;
  dynamic_string new_name = DYNAMIC_STRING_INITIALIZER;
  char *str_res;


  tty_in = fopen (TTY_NAME, "r");
  if (tty_in == NULL)
    error (PAXEXIT_FAILURE, errno, TTY_NAME);
  tty_out = fopen (TTY_NAME, "w");
  if (tty_out == NULL)
    error (PAXEXIT_FAILURE, errno, TTY_NAME);

  old_tape_des = tape_des;
  tape_offline (tape_des);
  rmtclose (tape_des);


  ++reel_number;
  if (new_media_message)
    fprintf (tty_out, "%s", new_media_message);
  else if (new_media_message_with_number)
    fprintf (tty_out, "%s%d%s", new_media_message_with_number, reel_number,
	     new_media_message_after_number);
  else if (archive_name)
    fprintf (tty_out, _("Found end of tape.  Load next tape and press RETURN. "));
  else
    fprintf (tty_out, _("Found end of tape.  To continue, type device/file name when ready.\n"));

  fflush (tty_out);

  if (archive_name)
    {
      int c;

      do
	c = getc (tty_in);
      while (c != EOF && c != '\n');

      tape_des = open_archive (archive_name);
      if (tape_des == -1)
	open_error (archive_name);
    }
  else
    {
      do
	{
	  if (tape_des < 0)
	    {
	      fprintf (tty_out,
		       _("To continue, type device/file name when ready.\n"));
	      fflush (tty_out);
	    }

	  str_res = ds_fgets (tty_in, &new_name);
	  if (str_res == NULL || str_res[0] == '\0')
	    exit (PAXEXIT_FAILURE);
	  next_archive_name = str_res;

	  tape_des = open_archive (next_archive_name);
	  if (tape_des == -1)
	    open_error (next_archive_name);
	}
      while (tape_des < 0);
    }


  if (tape_des != old_tape_des)
    error (PAXEXIT_FAILURE, 0, _("internal error: tape descriptor changed from %d to %d"),
	   old_tape_des, tape_des);

  ds_free (&new_name);
  fclose (tty_in);
  fclose (tty_out);
}
