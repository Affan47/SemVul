ephy_string_to_int (const char *string,
                    gulong     *integer)
{
  gulong result;
  char *parse_end;


  if (string == NULL || *string == '\0')
    return FALSE;


  errno = 0;
  result = strtol (string, &parse_end, 0);


  if (errno == ERANGE)
    return FALSE;


  while (*parse_end != '\0') {
    if (!g_ascii_isspace (*parse_end++))
      return FALSE;
  }


  *integer = result;
  return TRUE;
}
