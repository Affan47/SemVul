parsemsbrow(Logfile *lf, void *arg, char c) {
  Memman *m = (Memman *)arg;
  char *d;

  if (parsestring(lf, arg, c) == FALSE)
    return(FALSE);
  for (d = m->curr_pos; *d != '\0'; d++) {
    if (*d == '+')
      *d = ' ';
  }
  return(TRUE);
}
