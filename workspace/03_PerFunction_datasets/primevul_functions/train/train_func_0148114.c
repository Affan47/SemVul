static void resume (lua_State *L, void *ud) {
  int n = *(cast(int*, ud));
  StkId firstArg = L->top - n;
  CallInfo *ci = L->ci;
  if (L->status == LUA_OK) {
    luaD_call(L, firstArg - 1, LUA_MULTRET);
  }
  else {
    lua_assert(L->status == LUA_YIELD);
    L->status = LUA_OK;
    if (isLua(ci))
      luaV_execute(L, ci);
    else {
      if (ci->u.c.k != NULL) {
        lua_unlock(L);
        n = (*ci->u.c.k)(L, LUA_YIELD, ci->u.c.ctx);
        lua_lock(L);
        api_checknelems(L, n);
      }
      luaD_poscall(L, ci, n);
    }
    unroll(L, NULL);
  }
}
