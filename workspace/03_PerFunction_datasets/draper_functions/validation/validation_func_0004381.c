toLower(char* str)
{
  int i, len;
  len = strlen(str);
  for (i =0; i < len; i++) {
    str[i] = tolower(str[i]);
  }
  return str;
}
