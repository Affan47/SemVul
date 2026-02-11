lua_pushlstring (lua_State *L, const char *s, size_t len) {
  TString *ts;
  lua_lock(L);
  luaC_checkGC(L);
  ts = luaS_newlstr(L, s, len);
  setsvalue2s(L, L->top, ts);
  api_incr_top(L);
  lua_unlock(L);
  return getstr(ts);
}
