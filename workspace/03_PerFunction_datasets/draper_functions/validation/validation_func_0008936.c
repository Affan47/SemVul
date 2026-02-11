lua_pushboolean(lua_State *L, int b)
{
  setboolV(L->top, (b != 0));
  incr_top(L);
}
