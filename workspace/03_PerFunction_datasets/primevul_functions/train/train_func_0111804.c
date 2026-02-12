static int traverseephemeron (global_State *g, Table *h, int inv) {
  int marked = 0;
  int hasclears = 0;
  int hasww = 0;
  unsigned int i;
  unsigned int asize = luaH_realasize(h);
  unsigned int nsize = sizenode(h);

  for (i = 0; i < asize; i++) {
    if (valiswhite(&h->array[i])) {
      marked = 1;
      reallymarkobject(g, gcvalue(&h->array[i]));
    }
  }


  for (i = 0; i < nsize; i++) {
    Node *n = inv ? gnode(h, nsize - 1 - i) : gnode(h, i);
    if (isempty(gval(n)))
      clearkey(n);
    else if (iscleared(g, gckeyN(n))) {
      hasclears = 1;
      if (valiswhite(gval(n)))
        hasww = 1;
    }
    else if (valiswhite(gval(n))) {
      marked = 1;
      reallymarkobject(g, gcvalue(gval(n)));
    }
  }

  if (g->gcstate == GCSpropagate)
    linkgclist(h, g->grayagain);
  else if (hasww)
    linkgclist(h, g->ephemeron);
  else if (hasclears)
    linkgclist(h, g->allweak);
  else if (g->gckind == KGC_GEN)
    linkgclist(h, g->grayagain);
  else
    gray2black(h);
  return marked;
}
