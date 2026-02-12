static void traverseweakvalue (global_State *g, Table *h) {
  Node *n, *limit = gnodelast(h);


  int hasclears = (h->alimit > 0);
  for (n = gnode(h, 0); n < limit; n++) {
    if (isempty(gval(n)))
      clearkey(n);
    else {
      lua_assert(!keyisnil(n));
      markkey(g, n);
      if (!hasclears && iscleared(g, gcvalueN(gval(n))))
        hasclears = 1;
    }
  }
  if (g->gcstate == GCSatomic && hasclears)
    linkgclist(h, g->weak);
  else
    linkgclist(h, g->grayagain);
}
