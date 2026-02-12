int luaD_growstack (lua_State *L, int n, int raiseerror) {
  int size = L->stacksize;
  int newsize = 2 * size;
  if (unlikely(size > LUAI_MAXSTACK)) {
    if (raiseerror)
      luaD_throw(L, LUA_ERRERR);
    else return 0;
  }
  else {
    int needed = cast_int(L->top - L->stack) + n + EXTRA_STACK;
    if (newsize > LUAI_MAXSTACK)
      newsize = LUAI_MAXSTACK;
    if (newsize < needed)
      newsize = needed;
    if (unlikely(newsize > LUAI_MAXSTACK)) {

      luaD_reallocstack(L, ERRORSTACKSIZE, raiseerror);
      if (raiseerror)
        luaG_runerror(L, "stack overflow");
      else return 0;
    }
  }
  return luaD_reallocstack(L, newsize, raiseerror);
}
