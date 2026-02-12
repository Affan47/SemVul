static void finishCcall (lua_State *L, int status) {
  CallInfo *ci = L->ci;
  int n;

  lua_assert(ci->u.c.k != NULL && yieldable(L));

  lua_assert((ci->callstatus & CIST_YPCALL) || status == LUA_YIELD);
  if (ci->callstatus & CIST_YPCALL) {
    ci->callstatus &= ~CIST_YPCALL;
    L->errfunc = ci->u.c.old_errfunc;
  }


  adjustresults(L, ci->nresults);
  lua_unlock(L);
  n = (*ci->u.c.k)(L, status, ci->u.c.ctx);
  lua_lock(L);
  api_checknelems(L, n);
  luaD_poscall(L, ci, n);
}
