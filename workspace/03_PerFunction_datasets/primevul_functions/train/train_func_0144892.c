cgi_initialize_post(void)
{
  char		*content_length,
		*data;
  size_t	length,
		tbytes;
  ssize_t	nbytes;
  int		status;


  content_length = getenv("CONTENT_LENGTH");
  if (content_length == NULL || atoi(content_length) <= 0)
    return (0);


  length = (size_t)strtol(content_length, NULL, 10);
  data   = malloc(length + 1);

  if (data == NULL)
    return (0);


  for (tbytes = 0; tbytes < length; tbytes += (size_t)nbytes)
    if ((nbytes = read(0, data + tbytes, (size_t)(length - tbytes))) < 0)
    {
      if (errno != EAGAIN)
      {
        free(data);
        return (0);
      }
      else
        nbytes = 0;
    }
    else if (nbytes == 0)
    {


      free(data);
      return (0);
    }

  data[length] = '\0';


  status = cgi_initialize_string(data);


  free(data);

  return (status);
}
