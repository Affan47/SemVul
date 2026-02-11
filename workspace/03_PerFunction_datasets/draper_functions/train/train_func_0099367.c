process_file (char *infile, char *outfile, int crypttype)
{
  FILE *input;
  FILE *output;
  char *line;
  int i;

  if ((input = fopen (infile, "r")) == NULL)
    {
      perrorf ("Can't open the file `%s' for input", infile);
      return 1;
    }
  if (outfile == NULL)
    {
      output = stdout;
    }
  else if ((output = fopen (outfile, "w")) == NULL)
    {
      perrorf ("Can't open the file `%s' for output", outfile);
      return 1;
    }

  for (i = 1; (line = read_line (input, NULL)) != NULL; i++)
    {
      if (strncmp (line, "#", 1) == 0
	  || (strspn (line, " \t\r\n") == strlen (line)))
	{
	  fprintf (output, "%s", line);
	}
      else
	{
	  char *username, *password, *level, *dbs;
	  char *newpwentry;
	  if (parse_entry (line, &username, &password, &level, &dbs))
	    {
	      if (encrypt_ (password, crypttype, &newpwentry) == 1)
		{
		  fprintf (stderr, "Error: "
			   "MD5 encryption not supported on this system.\n");
		  free (line);
		  free (newpwentry);
		  return 1;
		}
	      fprintf (output, "%s:%s:%s:%s\n",
		       username, newpwentry, level, dbs);
	      free (newpwentry);
	    }
	  else
	    {
	      fprintf (stderr,
		       "Error: Unable to decode line %d of the file `%s'.\n",
		       i, infile);
	      free (line);
	      return 1;
	    }
	  free (line);
	}
    }

  fclose(input);
  fclose(output);

  return 0;
}
