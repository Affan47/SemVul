void luaE_enterCcall (lua_State *L) {
  int ncalls = getCcalls(L);
  L->nCcalls--;
  if (ncalls <= CSTACKERR) {
    luaE_freeCI(L);
    ncalls = getCcalls(L);
    if (ncalls <= CSTACKERR) {
      if (ncalls <= CSTACKERRMARK)
        luaD_throw(L, LUA_ERRERR);
      else if (ncalls >= CSTACKMARK) {

        L->nCcalls = (CSTACKMARK - 1);
        luaG_runerror(L, "C stack overflow");
      }


    }
  }
}
