remove_extra_coda (char *str)
{
  int len;
  while (*str != NULL_CHAR) {
    if (is_vowel (*str) && str[1] != '+' && !is_vowel (str[1]) && str[2] != '+' && str[2] != NULL_CHAR) {
      for (len = 2; str[len] != NULL_CHAR && str[len] != '+'; len++);
      memmove (str + 1, str + len, strlen (str + len) + 1);
      return (A68_TRUE);
    }
    str++;
  }
  return (A68_FALSE);
}
