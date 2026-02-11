Sexp_print_boolean(DOH *obj) {
    flush_parens();

    if (DohIsString(obj)) {
      if (atoi(Char(obj)) != 0)
	Printf(out, "t");
      else
	Printf(out, "nil");
    } else
      Printf(out, "nil");
  }
