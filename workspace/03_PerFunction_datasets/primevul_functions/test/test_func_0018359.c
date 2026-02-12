static void adjust_assign (LexState *ls, int nvars, int nexps, expdesc *e) {
  FuncState *fs = ls->fs;
  int needed = nvars - nexps;
  if (hasmultret(e->k)) {
    int extra = needed + 1;
    if (extra < 0)
      extra = 0;
    luaK_setreturns(fs, e, extra);
  }
  else {
    if (e->k != VVOID)
      luaK_exp2nextreg(fs, e);
    if (needed > 0)
      luaK_nil(fs, fs->freereg, needed);
  }
  if (needed > 0)
    luaK_reserveregs(fs, needed);
  else
    fs->freereg += needed;
}
