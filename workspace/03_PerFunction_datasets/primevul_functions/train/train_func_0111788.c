void luaC_changemode (lua_State *L, int newmode) {
  global_State *g = G(L);
  if (newmode != g->gckind) {
    if (newmode == KGC_GEN)
      entergen(L, g);
    else
      enterinc(g);
  }
  g->lastatomic = 0;
}
