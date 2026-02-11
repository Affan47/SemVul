rech_endtoken(const char *adr, const char **start) {
  char quote = '\0';
  int length = 0;

  while(is_space(*adr))
    adr++;
  if (*adr == '"' || *adr == '\'')
    quote = *adr++;
  *start = adr;
  while(*adr != 0 && *adr != quote && (quote != '\0' || !is_space(*adr))) {
    length++;
    adr++;
  }
  return length;
}
