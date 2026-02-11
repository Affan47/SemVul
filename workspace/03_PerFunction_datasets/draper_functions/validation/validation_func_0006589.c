string_is_complete(char *buf, int size)
{
  int i;

  if (buf[size-1] != 13 && buf[size-1] != 10) return 0;
  for (i = size-2;i >= 0;i--)
  {
    if (buf[i] == '}') return 1;
    if (buf[i] == '{') return 0;
  }
  return 1;
}
