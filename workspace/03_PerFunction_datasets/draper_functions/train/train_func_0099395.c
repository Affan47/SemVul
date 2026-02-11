main (int argc, char *argv[])
{
  GFile *file;
  GFileInputStream *in;
  GError *error;
  gssize res;
  gsize read_size;
  guchar *buffer;
  guchar start;
  gboolean do_create_file;

  do_create_file = FALSE;

  if (argc > 1)
    {
      if (strcmp(argv[1], "-c") == 0)
	{
	  do_create_file = TRUE;
	  argc--;
	  argv++;
	}
    }

  if (argc != 2)
    {
      g_print ("need file arg");
      return 1;
    }

  file = g_file_new_for_commandline_arg (argv[1]);

  if (do_create_file)
    create_file (file, 100*1000);

  error = NULL;

  in = g_file_read (file, NULL, &error);
  if (in == NULL)
    {
      g_print ("error reading file: %s\n", error->message);
      exit (1);
    }

  check_query_info (in, 100*1000);

  buffer = malloc (100*1000);

  start = 0;
  read_size = 0;
  do
    {
      res = g_input_stream_read  (G_INPUT_STREAM (in),
				  buffer,
				  150,
				  NULL, &error);
      if (res == 0)
	break;

      if (res < 0)
	{
	  g_print ("error reading: %s\n", error->message);
	  exit (1);
	}

      if (!verify_block (buffer, &start, res))
	{
	  g_print ("error in block starting at %d\n", (int)read_size);
	  exit (1);
	}

      read_size += res;

      check_query_info (in, 100*1000);
    }
  while (1);

  if (read_size != 100*1000)
    {
      g_print ("Didn't read entire file\n");
      exit (1);
    }

  main_loop = g_main_loop_new (NULL, FALSE);

  g_file_input_stream_query_info_async  (in, "*",
					 0, NULL,
					 async_cb, NULL);

  g_main_loop_run (main_loop);

  g_print ("ALL OK\n");
  return 0;
}
