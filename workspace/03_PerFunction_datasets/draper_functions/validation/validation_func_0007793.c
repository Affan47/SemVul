change(const char *str, char *from, char *to)
{
  char *copy = strdup(str);

  if (!copy)
    return NULL;

  char *pos  = strstr(copy, from);
  char *tmp  = NULL;

  while (pos) {
    *pos = '\0';
    tmp = snprintf_wrap("%s%s%s", copy, to, pos + strlen(from));
    if (tmp) {
      free(copy);
      copy = tmp;
    }
    pos = strstr(copy + strlen(to), from);
  }

  return copy;
}
