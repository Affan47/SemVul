cgi_initialize_multipart(
    const char *boundary)
{
  char		line[10240],
		name[1024],
		filename[1024],
		mimetype[1024],
		bstring[256],
		*ptr,
		*end;
  int		ch,
		fd;
  size_t	blen;


  name[0]     = '\0';
  filename[0] = '\0';
  mimetype[0] = '\0';

  snprintf(bstring, sizeof(bstring), "\r\n--%s", boundary);
  blen = strlen(bstring);

  while (fgets(line, sizeof(line), stdin))
  {
    if (!strcmp(line, "\r\n"))
    {


      if (filename[0])
      {


        if (form_file)
	{


	  cgi_unlink_file();
	}


	if ((form_file = calloc(1, sizeof(cgi_file_t))) == NULL)
	  return (0);

        form_file->name     = strdup(name);
	form_file->filename = strdup(filename);
	form_file->mimetype = strdup(mimetype);

        fd = cupsTempFd(form_file->tempfile, sizeof(form_file->tempfile));

        if (fd < 0)
	  return (0);

        atexit(cgi_unlink_file);


        ptr = line;

	while ((ch = getchar()) != EOF)
	{
	  *ptr++ = (char)ch;

          if ((size_t)(ptr - line) >= blen && !memcmp(ptr - blen, bstring, blen))
	  {
	    ptr -= blen;
	    break;
	  }

          if ((ptr - line - (int)blen) >= 8192)
	  {


	    write(fd, line, 8192);
	    memmove(line, line + 8192, (size_t)(ptr - line - 8192));
	    ptr -= 8192;
	  }
	}


	if (ptr > line)
          write(fd, line, (size_t)(ptr - line));

	close(fd);
      }
      else
      {


        ptr = line;
	end = line + sizeof(line) - 1;

	while ((ch = getchar()) != EOF)
	{
	  if (ptr < end)
	    *ptr++ = (char)ch;

          if ((size_t)(ptr - line) >= blen && !memcmp(ptr - blen, bstring, blen))
	  {
	    ptr -= blen;
	    break;
	  }
	}

	*ptr = '\0';


	if ((ptr = strrchr(name, '-')) != NULL && isdigit(ptr[1] & 255))
	{


	  *ptr++ = '\0';
	  if (line[0])
            cgiSetArray(name, atoi(ptr) - 1, line);
	}
	else if (cgiGetVariable(name))
	{


	  cgiSetArray(name, cgiGetSize(name), line);
	}
	else
	{


	  cgiSetVariable(name, line);
	}
      }


      fgets(line, sizeof(line), stdin);


      name[0]     = '\0';
      filename[0] = '\0';
      mimetype[0] = '\0';
    }
    else if (!_cups_strncasecmp(line, "Content-Disposition:", 20))
    {
      if ((ptr = strstr(line + 20, " name=\"")) != NULL)
      {
        strlcpy(name, ptr + 7, sizeof(name));

	if ((ptr = strchr(name, '\"')) != NULL)
	  *ptr = '\0';
      }

      if ((ptr = strstr(line + 20, " filename=\"")) != NULL)
      {
        strlcpy(filename, ptr + 11, sizeof(filename));

	if ((ptr = strchr(filename, '\"')) != NULL)
	  *ptr = '\0';
      }
    }
    else if (!_cups_strncasecmp(line, "Content-Type:", 13))
    {
      for (ptr = line + 13; isspace(*ptr & 255); ptr ++);

      strlcpy(mimetype, ptr, sizeof(mimetype));

      for (ptr = mimetype + strlen(mimetype) - 1;
           ptr > mimetype && isspace(*ptr & 255);
	   *ptr-- = '\0');
    }
  }


  return (1);
}
