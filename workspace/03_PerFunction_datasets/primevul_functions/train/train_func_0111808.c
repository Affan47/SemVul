static int traverseudata (global_State *g, Udata *u) {
  int i;
  markobjectN(g, u->metatable);
  for (i = 0; i < u->nuvalue; i++)
    markvalue(g, &u->uv[i].uv);
  if (g->gckind == KGC_GEN) {
    linkgclist(u, g->grayagain);
    black2gray(u);
  }
  return 1 + u->nuvalue;
}
