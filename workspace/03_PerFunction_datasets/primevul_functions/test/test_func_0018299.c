static void ifstat (LexState *ls, int line) {

  FuncState *fs = ls->fs;
  int escapelist = NO_JUMP;
  test_then_block(ls, &escapelist);
  while (ls->t.token == TK_ELSEIF)
    test_then_block(ls, &escapelist);
  if (testnext(ls, TK_ELSE))
    block(ls);
  check_match(ls, TK_END, TK_IF, line);
  luaK_patchtohere(fs, escapelist);
}
