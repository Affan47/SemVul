int luaD_rawrunprotected (lua_State *L, Pfunc f, void *ud) {
  global_State *g = G(L);
  l_uint32 oldnCcalls = g->Cstacklimit - (L->nCcalls + L->nci);
  struct lua_longjmp lj;
  lj.status = LUA_OK;
  lj.previous = L->errorJmp;
  L->errorJmp = &lj;
  LUAI_TRY(L, &lj,
    (*f)(L, ud);
  );
  L->errorJmp = lj.previous;
  L->nCcalls = g->Cstacklimit - oldnCcalls - L->nci;
  return lj.status;
}
