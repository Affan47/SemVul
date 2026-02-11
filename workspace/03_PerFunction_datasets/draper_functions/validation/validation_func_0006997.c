flags_to_string (u_int flags, char *def)
{
  static char string[128];
  char *prefix;

  string[0] = '\0';
  prefix = NULL;
  return (prefix == NULL && def != NULL ? def : string);
}
