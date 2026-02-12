l_noret luaD_throw (lua_State *L, int errcode) {
  if (L->errorJmp) {
    L->errorJmp->status = errcode;
    LUAI_THROW(L, L->errorJmp);
  }
  else {
    global_State *g = G(L);
    errcode = luaF_close(L, L->stack, errcode);
    L->status = cast_byte(errcode);
    if (g->mainthread->errorJmp) {
      setobjs2s(L, g->mainthread->top++, L->top - 1);
      luaD_throw(g->mainthread, errcode);
    }
    else {
      if (g->panic) {
        luaD_seterrorobj(L, errcode, L->top);
        if (L->ci->top < L->top)
          L->ci->top = L->top;
        lua_unlock(L);
        g->panic(L);
      }
      abort();
    }
  }
}
