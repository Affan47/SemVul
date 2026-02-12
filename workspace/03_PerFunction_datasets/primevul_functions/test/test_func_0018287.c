static void test_then_block (LexState *ls, int *escapelist) {

  BlockCnt bl;
  FuncState *fs = ls->fs;
  expdesc v;
  int jf;
  luaX_next(ls);
  expr(ls, &v);
  checknext(ls, TK_THEN);
  if (ls->t.token == TK_BREAK) {
    int line = ls->linenumber;
    luaK_goiffalse(ls->fs, &v);
    luaX_next(ls);
    enterblock(fs, &bl, 0);
    newgotoentry(ls, luaS_newliteral(ls->L, "break"), line, v.t);
    while (testnext(ls, ';')) {}
    if (block_follow(ls, 0)) {
      leaveblock(fs);
      return;
    }
    else
      jf = luaK_jump(fs);
  }
  else {
    luaK_goiftrue(ls->fs, &v);
    enterblock(fs, &bl, 0);
    jf = v.f;
  }
  statlist(ls);
  leaveblock(fs);
  if (ls->t.token == TK_ELSE ||
      ls->t.token == TK_ELSEIF)
    luaK_concat(fs, escapelist, luaK_jump(fs));
  luaK_patchtohere(fs, jf);
}
