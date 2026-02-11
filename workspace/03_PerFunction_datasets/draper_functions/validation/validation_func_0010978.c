Shortread_input_init (FILE *fp) {
  int c;
  bool okayp = false;

  Header[0] = '\0';

  while (okayp == false && (c = fgetc(fp)) != EOF) {
    debug(printf("Read character %c\n",c));
    if (iscntrl(c)) {
#ifdef DASH
    } else if (c == DASH) {
#endif
    } else if (isspace(c)) {
    } else {
      okayp = true;
    }
  }

  debug(printf("Returning initial character %c\n",c));
  return c;
}
