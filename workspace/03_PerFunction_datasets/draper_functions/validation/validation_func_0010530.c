fast_read_term(FILE *fin, FILE *fout)
{
  char line[MAX_LINE];
  char *s;
  Term t;
  s = fgets(line, MAX_LINE, fin);
  while (s != NULL && s[0] == '%')  {
    fprintf(stdout, "%s", s);
    fflush(stdout);
    s = fgets(line, MAX_LINE, fin);
  }
  if (s == NULL)
    return NULL;
  else {
    Pos = 0;
    t = fast_parse(s);
    if (s[Pos] != '.') {
      fprintf(stderr, s);
      fprintf(stdout, s);
      fatal_error("fast_read_term, term ends before period.");
    }
    return t;
  }
}
