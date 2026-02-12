static void fullinc (lua_State *L, global_State *g) {
  if (keepinvariant(g))
    entersweep(L);

  luaC_runtilstate(L, bitmask(GCSpause));
  luaC_runtilstate(L, bitmask(GCScallfin));

  lua_assert(g->GCestimate == gettotalbytes(g));
  luaC_runtilstate(L, bitmask(GCSpause));
  setpause(g);
}
