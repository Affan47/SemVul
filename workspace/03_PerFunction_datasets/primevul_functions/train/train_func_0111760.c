static void stepgenfull (lua_State *L, global_State *g) {
  lu_mem newatomic;
  lu_mem lastatomic = g->lastatomic;
  if (g->gckind == KGC_GEN)
    enterinc(g);
  luaC_runtilstate(L, bitmask(GCSpropagate));
  newatomic = atomic(L);
  if (newatomic < lastatomic + (lastatomic >> 3)) {
    atomic2gen(L, g);
    setminordebt(g);
  }
  else {
    g->GCestimate = gettotalbytes(g);  ;
    entersweep(L);
    luaC_runtilstate(L, bitmask(GCSpause));
    setpause(g);
    g->lastatomic = newatomic;
  }
}
