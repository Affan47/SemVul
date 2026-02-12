void luaC_fix (lua_State *L, GCObject *o) {
  global_State *g = G(L);
  lua_assert(g->allgc == o);
  white2gray(o);
  setage(o, G_OLD);
  g->allgc = o->next;
  o->next = g->fixedgc;
  g->fixedgc = o;
}
