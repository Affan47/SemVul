static void yindex (LexState *ls, expdesc *v) {

  luaX_next(ls);
  expr(ls, v);
  luaK_exp2val(ls->fs, v);
  checknext(ls, ']');
}
