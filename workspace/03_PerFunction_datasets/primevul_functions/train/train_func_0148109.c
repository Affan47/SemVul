static void moveresults (lua_State *L, StkId res, int nres, int wanted) {
  StkId firstresult;
  int i;
  switch (wanted) {
    case 0:
      L->top = res;
      return;
    case 1:
      if (nres == 0)
        setnilvalue(s2v(res));
      else
        setobjs2s(L, res, L->top - nres);
      L->top = res + 1;
      return;
    case LUA_MULTRET:
      wanted = nres;
      break;
    default:
      if (hastocloseCfunc(wanted)) {
        ptrdiff_t savedres = savestack(L, res);
        luaF_close(L, res, LUA_OK);
        res = restorestack(L, savedres);
        wanted = codeNresults(wanted);
        if (wanted == LUA_MULTRET)
          wanted = nres;
      }
      break;
  }
  firstresult = L->top - nres;

  for (i = 0; i < nres && i < wanted; i++)
    setobjs2s(L, res + i, firstresult + i);
  for (; i < wanted; i++)
    setnilvalue(s2v(res + i));
  L->top = res + wanted;
}
