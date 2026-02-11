typemapcopyDirective(Node *n) {
  String *method = Getattr(n, "method");
  Parm *pattern = Getattr(n, "pattern");
  Node *items = firstChild(n);
  int nsrc = 0;
  nsrc = ParmList_len(pattern);
  while (items) {
    ParmList *npattern = Getattr(items, "pattern");
    if (nsrc != ParmList_len(npattern)) {
      Swig_error(input_file, line_number, "Can't copy typemap. Number of types differ.\n");
    } else {
      if (Swig_typemap_copy(method, pattern, npattern) < 0) {
	Swig_error(input_file, line_number, "Can't copy typemap.\n");
      }
    }
    items = nextSibling(items);
  }
  return SWIG_OK;
}
