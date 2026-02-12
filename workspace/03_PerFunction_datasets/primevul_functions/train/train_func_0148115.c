LUA_API int lua_resume (lua_State *L, lua_State *from, int nargs,
                                      int *nresults) {
  int status;
  lua_lock(L);
  if (L->status == LUA_OK) {
    if (L->ci != &L->base_ci)
      return resume_error(L, "cannot resume non-suspended coroutine", nargs);
    else if (L->top - (L->ci->func + 1) == nargs)
      return resume_error(L, "cannot resume dead coroutine", nargs);
  }
  else if (L->status != LUA_YIELD)
    return resume_error(L, "cannot resume dead coroutine", nargs);
  if (from == NULL)
    L->nCcalls = CSTACKTHREAD;
  else
    L->nCcalls = getCcalls(from) + from->nci - L->nci - CSTACKCF;
  if (L->nCcalls <= CSTACKERR)
    return resume_error(L, "C stack overflow", nargs);
  luai_userstateresume(L, nargs);
  api_checknelems(L, (L->status == LUA_OK) ? nargs + 1 : nargs);
  status = luaD_rawrunprotected(L, resume, &nargs);

  while (errorstatus(status) && recover(L, status)) {

    status = luaD_rawrunprotected(L, unroll, &status);
  }
  if (likely(!errorstatus(status)))
    lua_assert(status == L->status);
  else {
    L->status = cast_byte(status);
    luaD_seterrorobj(L, status, L->top);
    L->ci->top = L->top;
  }
  *nresults = (status == LUA_YIELD) ? L->ci->u2.nyield
                                    : cast_int(L->top - (L->ci->func + 1));
  lua_unlock(L);
  return status;
}
