trim(char *str)
{
  size_t start;
  size_t term;

  if (!str)
    return NULL;

  start = 0;
  term  = strlen(str);

  while ((start < term) && isspace(str[start]))
    start++;
  while ((term > start) && isspace(str[term - 1]))
    term--;

  str[term] = '\0';


  if (start)
    memmove(str, str + start, term - start + 1);

  return str;
}
