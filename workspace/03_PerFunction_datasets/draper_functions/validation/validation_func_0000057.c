do_call (StkId base, int nResults)
{
  StkId firstResult;
  TObject *func = stack+base-1;
  int i;
  if (ttype(func) == LUA_T_CFUNCTION) {
    ttype(func) = LUA_T_CMARK;
    firstResult = callC(fvalue(func), base);
  }
  else if (ttype(func) == LUA_T_FUNCTION) {
    ttype(func) = LUA_T_MARK;
    firstResult = lua_execute(func->value.tf->code, base);
  }
  else {

    TObject *im = luaI_getimbyObj(func, IM_FUNCTION);
    if (ttype(im) == LUA_T_NIL)
      lua_error("call expression not a function");
    open_stack((top-stack)-(base-1));
    stack[base-1] = *im;
    do_call(base, nResults);
    return;
  }

  if (nResults != MULT_RET)
    adjust_top(firstResult+nResults);

  base--;
  nResults = top - (stack+firstResult);
  for (i=0; i<nResults; i++)
    *(stack+base+i) = *(stack+firstResult+i);
  top -= firstResult-base;
}
