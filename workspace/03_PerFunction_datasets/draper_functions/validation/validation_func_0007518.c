find_token_end(char *cur)
{
  char *n;
  for (n = cur; *n != ' ' && *n != '\0'; n++) {
    if (*n == '\\') {
      if (!n[1]) {
	return NULL;
      }
      n++;
    }
  }
  return n;
}
