static void GCTM (lua_State *L) {
  global_State *g = G(L);
  const TValue *tm;
  TValue v;
  lua_assert(!g->gcemergency);
  setgcovalue(L, &v, udata2finalize(g));
  tm = luaT_gettmbyobj(L, &v, TM_GC);
  if (!notm(tm)) {
    int status;
    lu_byte oldah = L->allowhook;
    int running  = g->gcrunning;
    L->allowhook = 0;
    g->gcrunning = 0;
    setobj2s(L, L->top++, tm);
    setobj2s(L, L->top++, &v);
    L->ci->callstatus |= CIST_FIN;
    status = luaD_pcall(L, dothecall, NULL, savestack(L, L->top - 2), 0);
    L->ci->callstatus &= ~CIST_FIN;
    L->allowhook = oldah;
    g->gcrunning = running;
    if (unlikely(status != LUA_OK)) {
      luaE_warnerror(L, "__gc metamethod");
      L->top--;
    }
  }
}
