alternation() {
  Expr left;

  left = concatenation();
  if (nav[idx] && !strcmp(nav[idx], "-o")) {
    skip();
    return build(or, left, concatenation());
  }
  else
    return left;
}
