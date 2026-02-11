indexupvalue (LexState *ls, expdesc *v) {
  FuncState *fs = ls->fs;
  int i;
  for (i=0; i<fs->nupvalues; i++) {
    if (fs->upvalues[i].k == v->k && fs->upvalues[i].u.index == v->u.index)
      return i;
  }

  luaX_checklimit(ls, fs->nupvalues+1, MAXUPVALUES, "upvalues");
  fs->upvalues[fs->nupvalues] = *v;
  return fs->nupvalues++;
}
