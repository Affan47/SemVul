static void leaveblock (FuncState *fs) {
  BlockCnt *bl = fs->bl;
  LexState *ls = fs->ls;
  int hasclose = 0;
  int stklevel = reglevel(fs, bl->nactvar);
  if (bl->isloop)
    hasclose = createlabel(ls, luaS_newliteral(ls->L, "break"), 0, 0);
  if (!hasclose && bl->previous && bl->upval)
    luaK_codeABC(fs, OP_CLOSE, stklevel, 0, 0);
  fs->bl = bl->previous;
  removevars(fs, bl->nactvar);
  lua_assert(bl->nactvar == fs->nactvar);
  fs->freereg = stklevel;
  ls->dyd->label.n = bl->firstlabel;
  if (bl->previous)
    movegotosout(fs, bl);
  else {
    if (bl->firstgoto < ls->dyd->gt.n)
      undefgoto(ls, &ls->dyd->gt.arr[bl->firstgoto]);
  }
}
