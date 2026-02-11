fast_parse(char *s)
{
  char c = s[Pos++];
  Term t;

  if (c >= 'r' && c <= 'z') {
    switch (c) {
    case 'z': t = get_variable_term(0); break;
    case 'y': t = get_variable_term(1); break;
    case 'x': t = get_variable_term(2); break;
    case 'w': t = get_variable_term(3); break;
    case 'v': t = get_variable_term(4); break;
    case 'u': t = get_variable_term(5); break;
    case 't': t = get_variable_term(6); break;
    case 's': t = get_variable_term(7); break;
    case 'r': t = get_variable_term(8); break;
    default:  t = NULL;
    }
    return t;
  }
  else {
    int i;
    if (Symnum[(int) c] == 0) {

      char str[2];
      str[0] = c; str[1] = '\0';
      Symnum[(int) c] = str_to_sn(str, 0);
    }
    t = get_rigid_term_dangerously(Symnum[(int) c], Arity[(int) c]);
    for (i = 0; i < Arity[(int) c]; i++) {
      ARG(t,i) = fast_parse(s);
    }
    return t;
  }
}
