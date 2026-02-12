cgiIsPOST(void)
{
  const char	*method;


  if ((method = getenv("REQUEST_METHOD")) == NULL)
    return (0);
  else
    return (!strcmp(method, "POST"));
}
