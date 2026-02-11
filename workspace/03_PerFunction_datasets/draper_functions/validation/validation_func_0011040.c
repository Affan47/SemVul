checknote() {

  int c;

  if (yylex() != NOTE || ((c=yylex()) != INT && c != NOTEVAL))
  syntax();
  if (c == NOTEVAL) {
    static int notes[] = {9, 11, 0, 2, 4, 5, 7};
    char *p = yytext;
    c = *p++;
    if (isupper(c)) c = tolower(c);
    yyval = notes[c-'a'];
    switch(*p) {
     case '#':
     case '+': yyval++; p++; break;
     case 'b':
     case 'B':
     case '-': yyval--; p++; break;
     }
     yyval += 12 * atoi(p);
  }
  if (yyval < 0 || yyval > 127)
    error("Note must be between 0 and 127");
  data[0] = yyval;
}
