lit_string_to_int(char *s)
{
  int i;
  if (str_to_int(s, &i))
    return i;
  else if (strlen(s) > 1)
    return INT_MIN;
  else
    return ctoi(s[0]);
}
