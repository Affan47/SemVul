static lu_mem entergen (lua_State *L, global_State *g) {
  lu_mem numobjs;
  luaC_runtilstate(L, bitmask(GCSpause));
  luaC_runtilstate(L, bitmask(GCSpropagate));
  numobjs = atomic(L);
  atomic2gen(L, g);
  return numobjs;
}
