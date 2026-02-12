int luaD_reallocstack (lua_State *L, int newsize, int raiseerror) {
  int lim = L->stacksize;
  StkId newstack = luaM_reallocvector(L, L->stack, lim, newsize, StackValue);
  lua_assert(newsize <= LUAI_MAXSTACK || newsize == ERRORSTACKSIZE);
  lua_assert(L->stack_last - L->stack == L->stacksize - EXTRA_STACK);
  if (unlikely(newstack == NULL)) {
    if (raiseerror)
      luaM_error(L);
    else return 0;
  }
  for (; lim < newsize; lim++)
    setnilvalue(s2v(newstack + lim));
  correctstack(L, L->stack, newstack);
  L->stack = newstack;
  L->stacksize = newsize;
  L->stack_last = L->stack + newsize - EXTRA_STACK;
  return 1;
}
