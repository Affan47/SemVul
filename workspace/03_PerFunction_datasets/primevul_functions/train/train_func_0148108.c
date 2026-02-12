void luaD_tryfuncTM (lua_State *L, StkId func) {
  const TValue *tm = luaT_gettmbyobj(L, s2v(func), TM_CALL);
  StkId p;
  if (unlikely(ttisnil(tm)))
    luaG_typeerror(L, s2v(func), "call");
  for (p = L->top; p > func; p--)
    setobjs2s(L, p, p-1);
  L->top++;
  setobj2s(L, func, tm);
}
