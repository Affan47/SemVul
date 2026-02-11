bits_to_int (NODE_T * p, char *str)
{
  int base = 0;
  unsigned bits = 0;
  char *radix = NO_TEXT, *end = NO_TEXT;
  RESET_ERRNO;
  base = (int) a68g_strtoul (str, &radix, 10);
  if (radix != NO_TEXT && TO_UPPER (radix[0]) == TO_UPPER (RADIX_CHAR) && errno == 0) {
    if (base < 2 || base > 16) {
      diagnostic_node (A68_RUNTIME_ERROR, p, ERROR_INVALID_RADIX, base);
      exit_genie (p, A68_RUNTIME_ERROR);
    }
    bits = a68g_strtoul (&(radix[1]), &end, base);
    if (end != NO_TEXT && end[0] == NULL_CHAR && errno == 0) {
      return (bits);
    }
  }
  diagnostic_node (A68_RUNTIME_ERROR, p, ERROR_IN_DENOTATION, MODE (BITS));
  exit_genie (p, A68_RUNTIME_ERROR);
  return (0);
}
