do_errlvl(gpasmVal r,
                          char *name,
                          int arity,
                          struct pnode *parms)
{
  struct pnode *p;
  state.lst.line.linetype = dir;

  if (state.pass == 2) {
    for (; parms; parms = TAIL(parms)) {
      p = HEAD(parms);
      if (p->tag == unop)  {
        gpasmVal value = evaluate(p->value.unop.p0);

        if (p->value.unop.op == '-') {
          add_code(-value);
        } else if (p->value.unop.op == '+') {
          add_code(value);
        } else {
          gperror(GPE_ILLEGAL_ARGU, "Expected 0, 1, 2, +|-<message number>");
        }
      } else if (p->tag == constant) {
        select_errorlevel(p->value.constant);
      } else {
        gperror(GPE_ILLEGAL_ARGU, "Expected 0, 1, 2, +|-<message number>");
      }
    }
  }

  return r;
}
