mailimap_date_month_send(mailstream * fd, int month)
{
  const char * name;
  int r;

  name = mailimap_month_get_token_str(month);

  if (name == NULL)
    return MAILIMAP_ERROR_INVAL;

  r = mailimap_token_send(fd, name);
    if (r != MAILIMAP_NO_ERROR)
      return r;

  return MAILIMAP_NO_ERROR;
}
