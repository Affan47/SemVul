luaU_undump(lua_State *L, ZIO *Z, Mbuffer *buff,
                      const char *name) {
  LoadState S;
  LClosure *cl;
  if (*name == '@' || *name == '=')
    S.name = name + 1;
  else if (*name == LUA_SIGNATURE[0])
    S.name = "binary string";
  else
    S.name = name;
  S.L = L;
  S.Z = Z;
  S.b = buff;
  checkHeader(&S);
  cl = luaF_newLclosure(L, LoadByte(&S));
  setclLvalue(L, L->top, cl);
  incr_top(L);
  cl->p = luaF_newproto(L);
  LoadFunction(&S, cl->p, NULL);
  lua_assert(cl->nupvalues == cl->p->sizeupvalues);
  luai_verifycode(L, buff, cl->p);
  return cl;
}
