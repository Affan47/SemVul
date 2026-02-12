static void singlevaraux (FuncState *fs, TString *n, expdesc *var, int base) {
  if (fs == NULL)
    init_exp(var, VVOID, 0);
  else {
    int v = searchvar(fs, n, var);
    if (v >= 0) {
      if (v == VLOCAL && !base)
        markupval(fs, var->u.var.vidx);
    }
    else {
      int idx = searchupvalue(fs, n);
      if (idx < 0) {
        singlevaraux(fs->prev, n, var, 0);
        if (var->k == VLOCAL || var->k == VUPVAL)
          idx  = newupvalue(fs, n, var);
        else
          return;
      }
      init_exp(var, VUPVAL, idx);
    }
  }
}
