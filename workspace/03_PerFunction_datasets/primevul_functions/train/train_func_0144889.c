cgi_initialize_get(void)
{
  char	*data;


  data = getenv("QUERY_STRING");
  if (data == NULL || strlen(data) == 0)
    return (0);


  return (cgi_initialize_string(data));
}
