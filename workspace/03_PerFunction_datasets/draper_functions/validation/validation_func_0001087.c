simpleexp (LexState *ls, vardesc *v) {
  check_debugline(ls);
  switch (ls->token) {
    case '(':
      next(ls);
      exp0(ls, v);
      check(ls, ')');
      break;

    case NUMBER:
      code_number(ls, ls->seminfo.r);
      next(ls);
      v->k = VEXP; v->info = 0;
      break;

    case STRING:
      code_string(ls, ls->seminfo.ts);
      next(ls);
      v->k = VEXP; v->info = 0;
      break;

    case NIL:
      adjuststack(ls, -1);
      next(ls);
      v->k = VEXP; v->info = 0;
      break;

    case '{':
      constructor(ls);
      v->k = VEXP; v->info = 0;
      break;

    case FUNCTION: {
      int line = ls->linenumber;
      next(ls);
      body(ls, 0, line);
      v->k = VEXP; v->info = 0;
      break;
    }

    case NAME: case '%':
      var_or_func(ls, v);
      break;

    default:
      luaX_error(ls, "<expression> expected");
      break;
  }
}
