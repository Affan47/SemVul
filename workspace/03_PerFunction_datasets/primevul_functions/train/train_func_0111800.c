static void traversestrongtable (global_State *g, Table *h) {
  Node *n, *limit = gnodelast(h);
  unsigned int i;
  unsigned int asize = luaH_realasize(h);
  for (i = 0; i < asize; i++)
    markvalue(g, &h->array[i]);
  for (n = gnode(h, 0); n < limit; n++) {
    if (isempty(gval(n)))
      clearkey(n);
    else {
      lua_assert(!keyisnil(n));
      markkey(g, n);
      markvalue(g, gval(n));
    }
  }
  if (g->gckind == KGC_GEN) {
    linkgclist(h, g->grayagain);
    black2gray(h);
  }
}
