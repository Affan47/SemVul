LUA_API int lua_setcstacklimit (lua_State *L, unsigned int limit) {
  global_State *g = G(L);
  int ccalls;
  luaE_freeCI(L);
  ccalls = getCcalls(L);
  if (limit >= 40000)
    return 0;
  limit += CSTACKERR;
  if (L != g-> mainthread)
    return 0;
  else if (ccalls <= CSTACKERR)
    return 0;
  else {
    int diff = limit - g->Cstacklimit;
    if (ccalls + diff <= CSTACKERR)
      return 0;
    g->Cstacklimit = limit;
    L->nCcalls += diff;
    return limit - diff - CSTACKERR;
  }
}
