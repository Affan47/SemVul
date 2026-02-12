parse_line (const char *line, char **com, char **val, int *comind)
{
  const char *p;
  const char *end = line + strlen (line);
  const char *cmdstart, *cmdend;
  const char *valstart, *valend;

  char *cmdcopy;
  int ind;


  while (*line && c_isspace (*line))
    ++line;
  while (end > line && c_isspace (end[-1]))
    --end;


  if (!*line || *line == '#')
    return line_empty;

  p = line;

  cmdstart = p;
  while (p < end && (c_isalnum (*p) || *p == '_' || *p == '-'))
    ++p;
  cmdend = p;


  while (p < end && c_isspace (*p))
    ++p;
  if (p == end || *p != '=')
    return line_syntax_error;
  ++p;
  while (p < end && c_isspace (*p))
    ++p;

  valstart = p;
  valend   = end;


  *com = strdupdelim (cmdstart, cmdend);
  *val = strdupdelim (valstart, valend);


  BOUNDED_TO_ALLOCA (cmdstart, cmdend, cmdcopy);
  dehyphen (cmdcopy);
  ind = command_by_name (cmdcopy);
  if (ind == -1)
    return line_unknown_command;


  *comind = ind;
  return line_ok;
}
