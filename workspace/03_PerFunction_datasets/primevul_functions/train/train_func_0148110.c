LUA_API int lua_yieldk (lua_State *L, int nresults, lua_KContext ctx,
                        lua_KFunction k) {
  CallInfo *ci = L->ci;
  luai_userstateyield(L, nresults);
  lua_lock(L);
  api_checknelems(L, nresults);
  if (unlikely(!yieldable(L))) {
    if (L != G(L)->mainthread)
      luaG_runerror(L, "attempt to yield across a C-call boundary");
    else
      luaG_runerror(L, "attempt to yield from outside a coroutine");
  }
  L->status = LUA_YIELD;
  if (isLua(ci)) {
    lua_assert(!isLuacode(ci));
    api_check(L, k == NULL, "hooks cannot continue after yielding");
    ci->u2.nyield = 0;
  }
  else {
    if ((ci->u.c.k = k) != NULL)
      ci->u.c.ctx = ctx;
    ci->u2.nyield = nresults;
    luaD_throw(L, LUA_YIELD);
  }
  lua_assert(ci->callstatus & CIST_HOOKED);
  lua_unlock(L);
  return 0;
}
