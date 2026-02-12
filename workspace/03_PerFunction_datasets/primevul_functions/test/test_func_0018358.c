static void labelstat (LexState *ls, TString *name, int line) {

  checknext(ls, TK_DBCOLON);
  while (ls->t.token == ';' || ls->t.token == TK_DBCOLON)
    statement(ls);
  checkrepeated(ls, name);
  createlabel(ls, name, line, block_follow(ls, 0));
}
