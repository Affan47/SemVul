void luaC_checkfinalizer (lua_State *L, GCObject *o, Table *mt) {
  global_State *g = G(L);
  if (tofinalize(o) ||
      gfasttm(g, mt, TM_GC) == NULL)
    return;
  else {
    GCObject **p;
    if (issweepphase(g)) {
      makewhite(g, o);
      if (g->sweepgc == &o->next)
        g->sweepgc = sweeptolive(L, g->sweepgc);
    }
    else {
      if (o == g->survival)
        g->survival = o->next;
      if (o == g->old)
        g->old = o->next;
      if (o == g->reallyold)
        g->reallyold = o->next;
    }

    for (p = &g->allgc; *p != o; p = &(*p)->next) {  }
    *p = o->next;
    o->next = g->finobj;
    g->finobj = o;
    l_setbit(o->marked, FINALIZEDBIT);
  }
}
