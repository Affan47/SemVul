static void gotostat (LexState *ls) {
  FuncState *fs = ls->fs;
  int line = ls->linenumber;
  TString *name = str_checkname(ls);
  Labeldesc *lb = findlabel(ls, name);
  if (lb == NULL)

    newgotoentry(ls, name, line, luaK_jump(fs));
  else {

    int lblevel = reglevel(fs, lb->nactvar);
    if (luaY_nvarstack(fs) > lblevel)
      luaK_codeABC(fs, OP_CLOSE, lblevel, 0, 0);

    luaK_patchlist(fs, luaK_jump(fs), lb->pc);
  }
}
