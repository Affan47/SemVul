void luaD_poscall (lua_State *L, CallInfo *ci, int nres) {
  if (L->hookmask)
    L->top = rethook(L, ci, L->top - nres, nres);
  L->ci = ci->previous;

  moveresults(L, ci->func, nres, ci->nresults);
}
