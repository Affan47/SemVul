_FP_strncpy (char *dest, char *src, int length)
{
  char *odest=dest;
  if (src == NULL || dest == NULL || length-- <= 0)
    return dest;

  while (length-- && *src)
    *dest++ = *src++;

  *dest++ = '\0';
  return odest;
}
