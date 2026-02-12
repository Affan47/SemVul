static lu_mem atomic (lua_State *L) {
  global_State *g = G(L);
  lu_mem work = 0;
  GCObject *origweak, *origall;
  GCObject *grayagain = g->grayagain;
  g->grayagain = NULL;
  lua_assert(g->ephemeron == NULL && g->weak == NULL);
  lua_assert(!iswhite(g->mainthread));
  g->gcstate = GCSatomic;
  markobject(g, L);

  markvalue(g, &g->l_registry);
  markmt(g);
  work += propagateall(g);

  work += remarkupvals(g);
  work += propagateall(g);
  g->gray = grayagain;
  work += propagateall(g);
  convergeephemerons(g);


  clearbyvalues(g, g->weak, NULL);
  clearbyvalues(g, g->allweak, NULL);
  origweak = g->weak; origall = g->allweak;
  separatetobefnz(g, 0);
  work += markbeingfnz(g);
  work += propagateall(g);
  convergeephemerons(g);


  clearbykeys(g, g->ephemeron);
  clearbykeys(g, g->allweak);

  clearbyvalues(g, g->weak, origweak);
  clearbyvalues(g, g->allweak, origall);
  luaS_clearcache(g);
  g->currentwhite = cast_byte(otherwhite(g));
  lua_assert(g->gray == NULL);
  return work;
}
