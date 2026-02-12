static int recover (lua_State *L, int status) {
  StkId oldtop;
  CallInfo *ci = findpcall(L);
  if (ci == NULL) return 0;

  oldtop = restorestack(L, ci->u2.funcidx);
  luaF_close(L, oldtop, status);
  oldtop = restorestack(L, ci->u2.funcidx);
  luaD_seterrorobj(L, status, oldtop);
  L->ci = ci;
  L->allowhook = getoah(ci->callstatus);
  luaD_shrinkstack(L);
  L->errfunc = ci->u.c.old_errfunc;
  return 1;
}
