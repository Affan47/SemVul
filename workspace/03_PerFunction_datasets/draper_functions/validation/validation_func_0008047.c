nss_parse_file (const char *fname)
{
  FILE *fp;
  name_database *result;
  name_database_entry *last;
  char *line;
  size_t len;


  fp = fopen (fname, "rce");
  if (fp == NULL)
    return NULL;


  __fsetlocking (fp, FSETLOCKING_BYCALLER);

  result = (name_database *) malloc (sizeof (name_database));
  if (result == NULL)
    {
      fclose (fp);
      return NULL;
    }

  result->entry = NULL;
  result->library = NULL;
  last = NULL;
  line = NULL;
  len = 0;
  do
    {
      name_database_entry *this;
      ssize_t n;

      n = __getline (&line, &len, fp);
      if (n < 0)
	break;
      if (line[n - 1] == '\n')
	line[n - 1] = '\0';


      *__strchrnul (line, '#') = '\0';


      if (line[0] == '\0')
	continue;


      this = nss_getline (line);
      if (this != NULL)
	{
	  if (last != NULL)
	    last->next = this;
	  else
	    result->entry = this;

	  last = this;
	}
    }
  while (!feof_unlocked (fp));


  free (line);

  fclose (fp);

  return result;
}
