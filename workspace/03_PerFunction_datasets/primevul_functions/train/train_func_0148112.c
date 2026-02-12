void luaD_pretailcall (lua_State *L, CallInfo *ci, StkId func, int narg1) {
  Proto *p = clLvalue(s2v(func))->p;
  int fsize = p->maxstacksize;
  int nfixparams = p->numparams;
  int i;
  for (i = 0; i < narg1; i++)
    setobjs2s(L, ci->func + i, func + i);
  checkstackGC(L, fsize);
  func = ci->func;
  for (; narg1 <= nfixparams; narg1++)
    setnilvalue(s2v(func + narg1));
  ci->top = func + 1 + fsize;
  lua_assert(ci->top <= L->stack_last);
  ci->u.l.savedpc = p->code;
  ci->callstatus |= CIST_TAIL;
  L->top = func + narg1;
}
