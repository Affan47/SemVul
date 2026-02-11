ReplaceFormat(const_String_or_char_ptr fmt, int j) {
  String *lfmt = NewString(fmt);
  char buf[50];
  sprintf(buf, "%d", j);
  Replaceall(lfmt, "$numargs", buf);
  int i;
  String *commaargs = NewString("");
  for (i = 0; i < j; i++) {
    Printv(commaargs, ", ", NIL);
    Printf(commaargs, Char(argv_template_string), i);
  }
  Replaceall(lfmt, "$commaargs", commaargs);
  return lfmt;
}
