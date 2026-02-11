fill_word(FILE *fp)
{
  int c;
  int i = 0;
  c = getc(fp);
  while (c != EOF && white_char(c))
    c = getc(fp);
  if (c != EOF) {
    while (c != EOF && !white_char(c) && !paren(c)) {
      Word[i] = c;
      i++;
      if (i == MAX_WORD) {
	Word[i] = '\0';
	fprintf(stderr, "fill_word, word too big: |%s|\n", Word);
	exit(2);
      }
      c = getc(fp);
    }
    if (c == ')' || (i != 0 && c == '('))
      ungetc(c, fp);
  }
  Word[i] = '\0';
  return(c);
}
