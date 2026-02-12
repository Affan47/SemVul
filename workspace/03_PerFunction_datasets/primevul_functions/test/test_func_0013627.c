static const char *getfuncname (lua_State *L, CallInfo *ci, const char **name) {

  if (ci != NULL && !(ci->callstatus & CIST_TAIL))
    return funcnamefromcall(L, ci->previous, name);
  else return NULL;
}
