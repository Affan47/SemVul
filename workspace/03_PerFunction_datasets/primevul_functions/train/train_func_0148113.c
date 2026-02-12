static void unroll (lua_State *L, void *ud) {
  CallInfo *ci;
  if (ud != NULL)
    finishCcall(L, *(int *)ud);
  while ((ci = L->ci) != &L->base_ci) {
    if (!isLua(ci))
      finishCcall(L, LUA_YIELD);
    else {
      luaV_finishOp(L);
      luaV_execute(L, ci);
    }
  }
}
