void luaC_freeallobjects (lua_State *L) {
  global_State *g = G(L);
  luaC_changemode(L, KGC_INC);
  separatetobefnz(g, 1);
  lua_assert(g->finobj == NULL);
  callallpendingfinalizers(L);
  deletelist(L, g->allgc, obj2gco(g->mainthread));
  deletelist(L, g->finobj, NULL);
  deletelist(L, g->fixedgc, NULL);
  lua_assert(g->strt.nuse == 0);
}
