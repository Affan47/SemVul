read_non_whitespace(FILE *f, byte *buff) {

  int i, good_char;
  byte c;

  good_char = 0;
  while (!good_char) {
    while (isspace(c = (char)fgetc(f)))
      ;
    if (c == '#')

      while ((c = (char)fgetc(f)) != '\n')
	;
    else
      good_char = 1;
  }
  i = 0;
  buff[i++] = c;
  while (!isspace(buff[i++] = (char)fgetc(f)))
    ;
  buff[--i] = 0;
}
